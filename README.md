# PEF3208
Calculadora de treliças isostáticas como trabalho para a disciplina PEF3208 de 2021.

O programa recebe como entradas nós, barras e forças de módulo, ângulo e ponto de aplicação conhecidos, analisa se o sistema está em equilíbrio e é isostático, e posteriormente calcula e salva as forças das barras em um arquivo de texto.

# O menu principal:
![image](https://user-images.githubusercontent.com/87289234/125497607-fcec2192-df79-4c69-9a85-3f8efbddd193.png)

Organizado por meio de funções numéricas, é através dele que todas as instruções serão enviadas.

# Inserir um nó:
![image](https://user-images.githubusercontent.com/87289234/125498045-9f981379-8bfc-4e81-b70b-5bbbd86dc409.png)

Ao selecionar a opção 1, o usuário deverá fornecer a posição no plano cartesiano do nó que deseja inserir. As coordenadas não estão restritas a valores inteiros, podendo assumir também valores decimais. Após o nó ser inserido, será exibido seu ID, que é importante para aplicar tanto as conexões de barras quanto para inserir as forças no sistema.

# Inserir uma barra:
![image](https://user-images.githubusercontent.com/87289234/125498637-20538c48-7262-4e01-8f4c-374767aa3523.png)

Para inserir uma barra através da opção 2, o usuário deverá fornecer os dois nós que serão conectados pela barra, através de seus respectivos IDs. Após realizar a conexão, será fornecido também o ID da nova barra.

# Inserir uma força:
![image](https://user-images.githubusercontent.com/87289234/125499022-e74c9298-88df-458d-88c2-eebef55cf0b5.png)

Ao inserir uma força através da opção 3, deverão ser informados o ângulo, módulo, e nó de aplicação da força. O valor do ângulo é medido em graus, com referencial igual ao do círculo trigonométrico. Tanto o módulo quanto o ângulo aceitam também valores decimais. O nó de aplicação é selecionado através de seu ID.

# Calcular:
![image](https://user-images.githubusercontent.com/87289234/125500222-6c2a270f-4912-4bb4-9bc8-4a5d6872bddf.png)

A operação de cálculo faz com que o programa verifique se a treliça atende às condições para ser calculada. Se a treliça é isostática e está em equilíbrio, as forças das barras são exibidas ao usuário, identificando a barra a qual pertencem através do ID da barra que acompanha a força entre os parênteses.

# Dados salvos:
![image](https://user-images.githubusercontent.com/87289234/125500853-39c31b96-4617-43ef-8c75-ccb7ec102c75.png)

Para que os valores das forças sejam facilmente copiados pelo usuário caso ele encerre o programa acidentalmente, todos os comandos para gerar a treliça são salvos, junto com os valores das forças calculadas. Para recriar a treliça rapidamente, basta colar o código da treliça diretamente no terminal do programa. O arquivo de salvamento "Ultima Trelica.txt" se encontra sempre no mesmo diretório do executável, e seus valores são limpos sempre que a treliça é deletada e sempre que o programa é reiniciado. Se desejar salvar os valores da treliça por mais tempo, faça uma cópia desse arquivo para outra pasta do computador.

# Apagar treliça:
![image](https://user-images.githubusercontent.com/87289234/125501607-a20f6b97-3a77-477a-a2ff-f7ec1216ee36.png)

Essa função limpa todos os valores inseridos anteriormente. É avisado também ao usuário que o arquivo de salvamento será limpo ao confirmar a operação, permitindo que ele realize uma cópia do arquivo caso queira.


