

def letters(text):
    letter = text.lower().replace(' ', '').replace('.', '').replace('!', '').replace('?', '').replace(';', '').replace(':', '').replace("\'", '').replace("\"", '').replace(',', '')
    return len(letter)

def words(text):
    words = text.split()
    return len(words)

def sentences(text):
    sentence = text.replace('!', '@').replace('.', '@').replace('?', '@')
    sentences = sentence.split('@')

    return len(sentences) - 1

def Coleman_Liau_index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    return index


def main():
    text = input('Text: ')
    letter_count = letters(text)
    words_count = words(text)
    sentence_count = sentences(text)
    index = Coleman_Liau_index(letter_count, words_count, sentence_count)

    if index >= 16:
        print('Grade 16+')
        return 0
    elif index < 1:
        print('Before Grade 1')
        return 0
    else:
        print(f'Grade {round(index)}')



if __name__ == '__main__':
    main()
