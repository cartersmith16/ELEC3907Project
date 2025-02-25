from string import Template
import random


def main():
    colours = ['Green', 'Blue', 'Red', 'Yellow']
    random_indices = random.sample(range(len(colours)), len(colours))

    d = {
        f'colour{i+1}': colours[random_indices[i]] for i in range(len(colours))
        }


    with open('resources/pdfTemplates/template.txt', 'r') as f:
        src = Template(f.read())
        result = src.substitute(d)
        print(result)
    
        text_file = open("resources/pdfTemplates/instructions.txt", "w")

        text_file.write(result)

        text_file.close()

main()

