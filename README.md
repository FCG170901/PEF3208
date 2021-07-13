# PEF3208
Calculadora de treliças isostáticas como trabalho para a disciplina PEF3208 de 2021.

O programa recebe como entradas nós, barras e forças de módulo, ângulo e ponto de aplicação conhecidos, analisa se o sistema está em equilíbrio e é isostático, e posteriormente calcula e salva as forças das barras em um arquivo de texto.

# O menu principal:
![image](https://user-images.githubusercontent.com/87289234/125497607-fcec2192-df79-4c69-9a85-3f8efbddd193.png)

Organizado por meio de funções numéricas, é através dele que todas as instruções serão enviadas.

# Inserir um nó:
![image](https://user-images.githubusercontent.com/87289234/125498045-9f981379-8bfc-4e81-b70b-5bbbd86dc409.png)

Ao selecionar a opção 1, o usuário deverá fornecer a posição no plano cartesiano do nó que deseja inserir. As coordenadas não esão restritas a valores inteiros, e podem assumir valores decimais. Após o nó ser inserido, será exibido seu ID, que é importante para aplicar tanto as conexões de barras quanto para inserir as forças no sistema.

# Inserir uma barra:
![image](https://user-images.githubusercontent.com/87289234/125498637-20538c48-7262-4e01-8f4c-374767aa3523.png)

Para inserir uma barra através da opção 2, o usuário deverá fornecer os dois nós que serão conectados pela barra, através de seus respectivos IDs. Após realizar a conexão, será fornecido também o ID da nova barra.

# Inserir uma força:
![image](https://user-images.githubusercontent.com/87289234/125499022-e74c9298-88df-458d-88c2-eebef55cf0b5.png)

Ao inserir uma força através da opção 3, deverão ser informados o ângulo, módulo, e nó de aplicação da força. O valor do ângulo é medido em graus, com referencial igual ao do plano cartesiano. Tanto o módulo quanto o ângulo aceitam também valores decimais. O nó de aplicação é selecionado através de seu ID.
