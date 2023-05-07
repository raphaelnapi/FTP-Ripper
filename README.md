# FTP-Ripper
Demonstração de ataque de dicionário a um servidor FTP

#Funcionamento
Organize o arquivo pass.txt de forma que ele contenha usuários e senhas separados por TAB.
Exemplo:
```
root	admin
root	admin1234
root	admin2020
root	admin20
root	root
root	root1234
admin	admin
admin	admin1234
admin	admin2020
admin	admin20
admin	root
```

Durante a execução do FTP Ripper, a aplicação criará o arquivo relatorio.txt que irá conter os usuários e senhas do arquivo pass.txt já testados. Criará também o arquivo senhas encontradas.txt no caso de realizar login com sucesso.

Exemplo arquivo relatorio.txt:
```
teste	teste	[ACESSO NEGADO]
root	admin	[ACESSO NEGADO]
root	admin1234	[ACESSO NEGADO]
root	admin2020	[ACESSO NEGADO]
root	admin20	[ACESSO NEGADO]
sgon4rd	sgon4rd	[ACESSO AUTORIZADO]
root	root	[ACESSO NEGADO]
root	root1234	[ACESSO NEGADO]
root	root20	[ACESSO NEGADO]
```

Exemplo arquivo senhas encontradas.txt:
```
sgon4rd	sgon4rd	[ACESSO AUTORIZADO]
```
