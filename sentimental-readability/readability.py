from cs50 import get_string

letters = 0
words = 1
sentences = 0

text = get_string("Text: ")

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace():
        words += 1
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1

av_letters = letters / words * 100
av_sentences = sentences / words * 100
index = round(0.0588 * av_letters - 0.296 * av_sentences - 15.8)

if index > 16:
    print("Grade 16+")
elif index > 1 and index < 17:
    print(f"Grade {index}")
else:
    print("Before Grade 1")
