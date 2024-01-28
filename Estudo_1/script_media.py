def calcular_media(arquivo):
    with open(arquivo, 'r') as f:
        linhas = f.readlines()[:10]  # Lê as 10 primeiras linhas
        valores = [float(linha.strip()) for linha in linhas]  # Converte os valores para float

        if valores:
            media = sum(valores) / len(valores)
            return media
        else:
            return None  # Retorna None se não houver valores

# Substitua 'seu_arquivo.txt' pelo nome do seu arquivo
arquivo = input()
media = calcular_media(arquivo)

if media is not None:
    print(f'95 Thread média: {media}')
else:
    print('Não há valores suficientes para calcular a média.')
