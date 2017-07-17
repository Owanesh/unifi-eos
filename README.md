![UnifiEosLogo](https://raw.githubusercontent.com/Owanesh/unifi-eos/master/resources/img/repo_logo.jpg)
# unifi-EOS
#### Università degli studi di Firenze

Questa repository è stata creata per un esame universitario della Facoltà di Informatica, corso di Sistemi Operativi.


_Per maggiori informazioni sullo sviluppo e sull'analisi del codice, si prega di consultare la [wiki](https://github.com/Owanesh/unifi-eos/wiki)._

**La repository non sarà mantenuta oltre la consegna (e fine) del progetto.**

## Come compilare ?

**Scheduler**
```sh
cd scheduler/
make -f scheduler.make
./scheduler
```
**Interpreter**
```sh
cd interpreter/
make -f interpreter.make
./interpreter
```

**Chat**

_Server_
```sh
cd chat_server/
make -f chat_server.make
./chat_server
```
_Client_
```sh
cd chat_client/
make -f chat_client.make
./chat_client
```

## ⚡️ Extra
#### Chat
```sh
cd <yourgitfolder>
mkdir executables
mv chat_client/src/chat_client executables/chat_client
mv chat_server/src/chat_server executables/chat_server
cd executables
./chat_server
./chat_client
```
E' necessario che entrambi i programmi stiano nella stessa cartella [Vedi Commit](https://github.com/Owanesh/unifi-eos/commit/8e87d6e8a9e8d42d48375ec8397313fd57213690) 👈

![Win](https://media.giphy.com/media/XE7kcG4fMEDqU/giphy.gif)

Testato su
* Mac OSX Sierra
* Ubuntu 12.0.4 LTS

***
Made with ❤️  by [Owanesh](https://github.com/Owanesh) and [MatteoMauro](https://github.com/MatteoMauro)
