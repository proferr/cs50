import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, is_int

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""



    rows = db.execute(
        "SELECT id, symbol, price, SUM(shares) as shares FROM trades WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0 ORDER BY price DESC", session["user_id"])

    total = 0
    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = quote["price"]
        row["total_price"] = quote["price"] * row["shares"]
        total += row["total_price"]

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    cash = user_cash[0]["cash"]

    return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        TYPE = "buy"

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide valid symbol", 400)

        shares = request.form.get("shares")
        if not shares or not is_int(shares):
            return apology("must provide shares", 400)

        if int(shares) <= 0:
            return apology("share number can't be negative number or zero", 400)


        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)
        else:
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            total_cost = quote["price"] * int(shares)

            if total_cost > user_cash[0]["cash"]:
                return apology("no cash", 400)
            else:
                db.execute("INSERT INTO trades (id, symbol, name, shares, price, type) VALUES(?, ?, ?, ?, ?, ?)",
                           session["user_id"], quote["symbol"], quote["name"], int(shares), quote["price"], TYPE)
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           user_cash[0]["cash"] - total_cost, session["user_id"])
                return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_transactions = db.execute(
        "SELECT id, symbol, shares, price, transacted, type FROM trades WHERE id = ? ORDER BY transacted", session["user_id"])

    return render_template("history.html", user_transactions=user_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)
        else:
            return render_template("quoted.html", quote=quote)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must provide password confirmation", 400)

        if password != confirmation:
            return apology("Passwords don't match", 400)
        else:
            password = generate_password_hash(password, method='scrypt', salt_length=16)

        check = db.execute("SELECT username FROM users WHERE username = ?", username)
        if check:
            return apology("Username already registered", 400)

        # Insert data into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        TYPE = "sell"
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide valid symbol", 400)

        shares = request.form.get("shares")
        if not shares or not is_int(shares):
            return apology("must provide shares", 400)

        if int(shares) <= 0:
            return apology("share number can't be negative number or zero", 400)

        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)

        rows = db.execute(
            "SELECT id, symbol, SUM(shares) as shares FROM trades WHERE id = ? AND symbol = ? GROUP BY symbol HAVING SUM(shares) > 0 ",
            session["user_id"], quote['symbol'])

        user_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        if rows[0]["shares"] < int(shares):
            return apology("too many shares", 400)

        else:
            total_price = quote["price"] * int(shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash[0]["cash"] + total_price, session["user_id"])
            db.execute("INSERT INTO trades (id, symbol, name, shares, price, type) VALUES(?, ?, ?, ?, ?, ?)",
                       session["user_id"], quote["symbol"], quote["name"], -int(shares), quote["price"], TYPE)
        return redirect("/")

    else:
        rows = db.execute(
            "SELECT id, symbol, SUM(shares) FROM trades WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0 ORDER BY symbol", session["user_id"])

        return render_template("sell.html", rows=rows)
