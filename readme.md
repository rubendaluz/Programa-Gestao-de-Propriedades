Este trabalho tem como principal objetivo analisar e implementar, na linguagem C, uma
aplicação de avaliação de propriedades rurais, que pretende apoiar os seus utilizadores no
processo da avaliação.
O programa é gerido pelos administradores que podem registar novos utilizadores. Cada
utilizador tem um username único, um nome, uma password, e um tipo (administrador,
avaliador).
Uma propriedade rural tem associadas várias informações, nomeadamente o seu número
(sequencial); o identificador; o nome do proprietário; a descrição da propriedade; a área total;
uma lista de até vinte culturas cultivadas na propriedade (ex: milho, centeio, etc.), que contém
uma descrição e a área da cultura em m2. A propriedade deve conter ainda um estado da
avaliação que pode ter um dos seguintes valores: “para avaliar”, “em avaliação”, “avaliado”.
Quando a avaliação passa ao estado “avaliado”, são registados mais alguns campos de
informação, nomeadamente: o valor da avaliação, a data, e ainda o utilizador do tipo “avaliador”
que analisou a propriedade e estipulou o valor.
O sistema deve permitir operações básicas de inserir, alterar, apagar, pesquisar/listar (aka
CRUD) sobre os dados das propriedades rurais. Estas operações são efetuadas exclusivamente
por utilizadores do tipo administrador.
Sempre que um pedido de avaliação é inserido fica no estado “para avaliar” e o sistema deve
sinalizar o pedido para avaliação numa fila própria para o efeito. A avaliação é efetuada por
ordem de chegada. A pessoa que avalia deve ser um utilizador do tipo “avaliador”, que deve
decidir sobre a próxima propriedade da fila. Durante o processo de avaliação, a propriedade
passa ao estado “em avaliação”. Assim que finalizada a avaliação, a propriedade passa para o
estado “avaliado”, com preenchimento dos campos referidos acima.
O sistema deve permitir aos administradores diversas listagens e relatórios sobre as
propriedades rurais e métricas associadas, nomeadamente:
• listar as propriedades por analisar;
• listar todas as propriedades avaliadas e o valor;
• listar todas as propriedades com avaliações acima de um dado valor;
• listar todas as propriedades avaliadas por um determinado utilizador do tipo
“avaliador”, ordenadas primeiro por data da avaliação, e depois por valor;
• pesquisar propriedades por nome do proprietário;
• escrever num ficheiro de texto um relatório com propriedade avaliadas, ordenadas por
valor;
• gerar o ranking de utilizadores por número de propriedades avaliadas.
A aplicação deve ainda garantir que o seu estado de execução é guardado em ficheiro binário
para que mais tarde possa ser restaurado, garantindo assim continuidade de funcionamento
entre utilizações.