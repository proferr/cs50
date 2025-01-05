import qrcode

from flask import Flask, flash, redirect, render_template, request
from flask_qrcode import QRcode

from helpers import apology, phone_format, parse_url

# Configure application
app = Flask(__name__)

# Configure QRCode
QRcode(app)


@app.route("/", methods=["GET", "POST"])
def index():
    """Make visible QR Code"""

    if request.method == "POST":
        type = request.form.get("type")
        if not type:
            return apology("Must be Type", 400)
        else:
            match type:
                case "link":
                    content = request.form.get("link")
                    if not content:
                        return apology("Must be a link", 400)
                    else:
                        return render_template("index.html", content=content)
                case "text":
                    content = request.form.get("textarea")
                    return render_template("index.html", content=content)
                case "whatsapp":
                    phone = phone_format(request.form.get("phone"))
                    message = parse_url(request.form.get("message"))
                    content = f"wa.me/{phone}?text={message}"
                    return render_template("index.html", content=content)
    else:
        type = request.args.get("type")
        if not type:
            return render_template("index.html")
        else:
            return render_template("typeform.html", type=type)


@app.route("/link")
def link():
    """Link route"""

    if request.method == "POST":
        content = request.form.get("textarea")
        return render_template("index.html", content=content)
    else:
        return render_template("text.html")


@app.route("/text")
def text():
    """Text route"""

    if request.method == "POST":
        content = request.form.get("link")
        return render_template("index.html", content=content)
    else:
        return render_template("link.html")


@app.route("/email")
def email():
    """Email route"""

    if request.method == "POST":
        content = request.form.get("email")
        return render_template("index.html", content=content)
    else:
        return render_template("email.html")


@app.route("/whatsapp")
def whatsapp():
    """Whatsapp route"""

    if request.method == "POST":
        phone = phone_format(request.form.get("phone"))
        message = urllib.parse.quote(request.form.get("message"))
        content = f"wa.me/{phone}?text={message}"
        return render_template("index.html", content=content)
    else:
        return render_template("whatsapp.html")
        #return render_template("typeform.html", type=type)


@app.route("/about")
def about():
    """About this APP"""

    return render_template("about.html")
