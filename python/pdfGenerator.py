from string import Template
d = {
    'title': 'This is the title',
    'name': 'Johnny Sins',
    'food': '\n'.join(['aples', 'oranges', 'pears'])
}

with open('resources/pdfTemplates/template.txt', 'r') as f:
    src = Template(f.read())
    result = src.substitute(d)
    print(result)
    
    text_file = open("resources/pdfTemplates/instructions.txt'", "w")

    text_file.write(result)

    text_file.close()