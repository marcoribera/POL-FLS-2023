# Projeto Servidor Ultima Online FLS 2023

Este projeto utiliza a engine POL v100 para criar um servidor de Ultima Online.

## Instru��es de Instala��o

1. Baixe a vers�o do POL correspondente ao seu sistema operacional em [POL Server](https://github.com/polserver/polserver/releases).
2. Extraia o arquivo em uma pasta separada.
3. Copie as seguintes pastas e execut�veis para a pasta do projeto:
   - pol
   - poltool
   - uoconvert
   - uotool
   - scripts/ecompile
   - scripts/modules/

   **Nota:** N�o copie nenhum outro arquivo, pois s�o arquivos de configura��o.

4. Abra o arquivo pol.cfg e altere UoDataFileRoot para o caminho do seu Ultima Online com os arquivos do shard.
5. Se estiver usando Linux, instale a libmysqlclient2 com o comando `apt-get install libmysqlclient2`.
6. Carregue o mapa do servidor usando o uoconvert com os seguintes comandos:
   - `./uoconvert map     realm=britannia mapid=0 usedif=1 width=6144 height=4096`
   - `./uoconvert statics realm=britannia`
   - `./uoconvert maptile realm=britannia`

7. Crie uma c�pia da pasta /data_dev/ e renomeie para /data. Altere as informa��es no arquivo /data/accounts.txt para criar sua conta.
8. Para compilar todos os scripts, abra o terminal na pasta do projeto e execute o comando `scripts/ecompile -a`.

Agora voc� est� pronto para iniciar seu servidor Ultima Online!
