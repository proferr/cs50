# FREE QR CODE

## CS50
>This was my final project for conclude the CS50 Introduction to Computer Sciense course.

>CS, python, flask, flask web framework, web development, CS50

#### Video Demo: https://youtu.be/Q1-EBhlxXcg
#### Description:
The Free QR Code app is a web-based application written in python using flask. The aim of the app is to generate QR Codes for links, text messages and especially instant whatsapp conversations.

The project files follow the layout guidelines of [Flask](https://flask.palletsprojects.com/en/2.3.x/tutorial/layout/), but in a simplified manner. The root files are `app.py` and `helpers.py`, serving as the **backend** of the application. Regarding the **frontend**, it is divided into two folders: `static` and `templates`. These folders host user-interactive functionality scripts, a style sheet and svgs, and HTML content, respectively.

## Backend
### [`app.py`](/app.py)
This file defines most of the logic for receiving the forms for each type of QR Code that can be generated. Each of the available QR Code types is separated into different routes.

The next lines of code refer to the different routes of the application:
- [`index`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L16)
- [`link`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L48)
- [`text`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L59)
- [`email`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L70)
- [`whatsapp`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L81)
- [`about`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/app.py#L95)

### [`helpers.py`](/app.py)
This file has some auxiliary functions, such as phone number formatting for the E164 standard and URL parsing for text messages.

Here is the list:
- [`apology`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/helpers.py#L7)
- [`phone_format`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/helpers.py#L32)
- [`parse_url`](https://github.com/me50/proferr/blob/075483699ce09b6b4b003f7b6a7b2e7aaca36bde/helpers.py#L40)

## Frontend
## The international code library
I used the __intl-tel-input__ javascript library to convert the international area code into country flags. In app.py I sanitize the telephone string by converting it into the __E164 format__.
Available at this link: https://cdnjs.cloudflare.com/ajax/libs/intl-tel-input/17.0.8/js/utils.js

```javascript
    const phoneInputField = document.querySelector("#phone");
    const phoneInput = window.intlTelInput(phoneInputField, {
    utilsScript:
        "https://cdnjs.cloudflare.com/ajax/libs/intl-tel-input/17.0.8/js/utils.js",
    });
```

## The proposed design for the qrcode type
My biggest challenge was to load input fields according to the qrcode type. To solve the challenge, I used buttons to change the __TYPE__ parameter in the URL, rendering a subtemplate with only the necessary fields. This generated some duplication!

After a while I opted to use the qr code types as routes:

```python
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
```

## Project Files
For the whole project, I only used the __app.py__ file with the index route and a __helper.py__ file with a phone formatting function (phone_format), and the apology function for 400 returns.

### Templates
Here I've created the __typeform.html__ template with the conditional form fields according to the type of code. Did I mention any duplication? lol

## Demonstration on youtube
For the CS50 final project you have to make a video showning your project,
[My Final Project presentation](https://youtu.be/Q1-EBhlxXcg)

## App Logo
The project logo was designed in illustrator using the main colors of Harvard Business School superimposed on a QR Code. I like that.
<img src="static/logo.webp" width="400">

## Sources
- [CS50X](https://cs50.harvard.edu/x/2024/)
- [Flask docs](https://flask.palletsprojects.com/en/2.3.x/)
- [Jinja docs](https://jinja.palletsprojects.com/en/3.1.x/)
- [Python docs](https://docs.python.org/3/)
- [Bootstrap docs](https://getbootstrap.com/docs/5.3/getting-started/introduction/)
