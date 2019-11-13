Para fazer um driver do linux temos duas opções, podemos fazer um modulo que seja compilado junto ao kernel ou simplesmente fazer um driver para ser carregado como um modulo vindo do user-space e é isso que vamos fazer desenvolver um driver para fazer uma conn virtual que comunique com seu pc

para isso precisamos de um codigo fonte que sera feito em c

primeiramente precisamo incluir a biblioteca de modulos do linux, para faremos um novo arquivo chamado de tcom.c

```sh
touch tcom.c
```

precisamos adicionar os headers no nosso arquivo tambem
```sh
nano tcom.c
```

dentro do arquivo temos que adicionar as duas linhas de bibliotecas para que possamos usar as funções que conversam com o kernel alem de poder usar seus macros

```C
#include <linux/init.h>
#include <linux/module.h>


```

com as bibliotecas importadas podemos começar o nosso codigo como por exemplo fazer dizer o que nosso driver fará ao ser carregado e descarregado.

https://github.com/torvalds/linux/tree/f1f2f614d535564992f32e720739cb53cf03489f/include/linux/module.h#L72-L74


 essas funções tem um padrão para se seguir em que a função de inicialização retorna um inteiro e o exit nao retorna nada
como mostrado acima


```C
static int init_com(void)
{
    return  0;
}
   
static void finish_com(void)
{
    return;
}

module_init(init_com);
module_exit(finish_com);

```

essas duas funcoes podem ser chamadas pelas macros module_init e module_exit, que vao ser chamados no momento de inicio do modulo e saida do modulo

https://github.com/torvalds/linux/blob/f1f2f614d535564992f32e720739cb53cf03489f/include/linux/module.h#L76-L107

tem tambem muitas outra opções para definir o autor do módulo e ate mesmo a licensa dele, mas nao entraremos em muitos detalhes


Podemos por exemplo fazer um driver que simplesmente mande um Hello World para o kernel quando ele é inicializado para isso semelhante a um programa em C utilizaremos uma função print

precisamos importar mais uma biblioteca para que essa função fique disponivel

```C
#include <linux/kernel.h>
```

com essa funcão importada temos acesso ao printk uma função que printa ao log do kernel


Ate agora temos um programa assim

```C
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int init_com(void)
{
    printk("\nHello World\n");
    return  0;
}
   
static void finish_com(void)
{
    return;
}

module_init(init_com);
module_exit(finish_com);
```


podemos entao compilar o nosso programa usando uma Makefile contendo


```Makefile
obj-m := tcom.o
```


usamos tambem por padrao o lib modules do nosso sistema que esta localizado em ```/lib/modules/$(uname -r)/build``` 
## se for testar no seu linux deixe /lib/modules/$(uname -r)/build
ou podemos gerar nosso proprio com um kernel do linux 

```bash
make modules_install INSTALL_MOD_PATH=/some/root/folder
```

ou simplesmente dentro da sua pasta do linux

```bash
make modules
```

usando

```bash
make -C /path/para/source/linux M=`pwd` modules

```

para compilar

com isso teremos um arquivo .ko que para todos os fins é o nosso driver, este pode ser carregado e descarregado usando insmod e rmmod respectivamente

como uma simples demosntração podemos abrir um terminal e observar os logs do linux

```bash
tail -f /var/log/kern.log
```

enquanto em outro terminal compilamos o modulo e carregamos ele

```bash
make -C /path/para/source/linux M=`pwd` modules
sudo insmod ./tcom.ko
sudo rmmod ./tcom.ko

```

depois de executar esses comandos no linux voltamos ao nosso terminal que esta acompanhando o log do kernel e vemos que com sucesso obtivemos a mensagem

```log
kernel: [666.1337] Hello World
```

