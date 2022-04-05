Projeto Final Sistemas Operacionais

Integrantes:

Carlos Eduardo Cardia Fernandez - 11911EMT016
Gessyca Carneiro Bernandes - 11911EMT022
Laura Bueno Ferreira - 11911EMT017
Talles Martins de Carvalho - 11911EMT014

Visão Geral:

	O projeto consiste em fazer um algoritmo do banqueiro, em que foi feito a alocação de recursos no sistema operacional, 
	o objetivo foi de simular mútiplos processos em que cada um faz alguma requisição e a execução precisa garantir o estado 
	seguro da alocação. O banqueiro permite ou não a alocação de uma requisição de recurso.

Recursos Alocados:
	 
	Representados pela "MatrizUso", correspondem aos recursos que já estão em uso e alocados
	em determinados processos. Esses recursos podem ser realocados e redistribuídos pelo
	sistema na hora de atender uma requisição.

Recursos Disponíveis:

	Correspondem aos recursos disponíveis de cada tipo, sendo esses os que não estão sendo
	usados e que podem ser alocados. São representados pela "MatrizRec".

Recursos Necessários:

	São equivalentes aos recursos solicitados na requisição de cada processo, correspondem
	ao total necessário para cada um ser executado. Representados por meio da "MatrizNec".


Recursos Faltosos:

	São representados pela "MatrizFal" e correspondem aos recursos que precisarão efetivamente
	ser alocados pelo sistema para atender a requisição de cada processo. Assim, são a 
	diferença entre os recursos necessários e os recursos que já estão alocados.

Processos:

	Os processos foram simulados a partir das threads, que farão requisição aleatória de 
	recursos. 

Algoritmo do Banqueiro:

	A partir das requisições feitas pelas threads, o algoritmo irá realizar as seguintes
	verificações na função "obterRec": 

	- Nenhum processo receberá mais recursos que os totais disponíveis;
	- Todos os processos receberão recursos limitados;

	Essas verificações foram feitas por meio das funções: "SeMaiorQueNec(pID,requisicao)"
	"SuficienteParaAlocar(requisicao)" e "modoseguro()" 

	Além disso, ocorre a liberação aleatória desses recursos requisitados por meio da função
	"liberaRec", em que ocorre as seguintes verificações:

	- Nenhum processo pode receber mais recursos que o limite;
	- A soma de todos os recursos alocados não pode ser maior que os recursos totais
	disponíveis;
	

	



