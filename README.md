![UnifiEosLogo](https://raw.githubusercontent.com/Owanesh/unifi-eos/master/resources/img/repo_logo.jpg)
# unifi-EOS
#### Università degli studi di Firenze

Questa repository è stata creata per un esame universitario della Facoltà di Informatica, corso di Sistemi Operativi.


_Per maggiori informazioni sullo sviluppo e sull'analisi del codice, si prega di consultare la wiki._

**La repository non sarà mantenuta oltre la consegna (e fine) del progetto.**

### Come partire ?

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
make -f server.make
./chat_server
```
_Client_
```sh
cd chat_client/
make -f chat_client.make
./chat_client
```

Testato su
* Mac OSX Sierra
* Ubuntu 12.0.4

***
Made with ❤️  by [Owanesh](https://github.com/Owanesh) and [MatteoMauro](https://github.com/MatteoMauro)
