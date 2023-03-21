#include <iostream>
#include <cstdlib> // para usar system pause
#include <ctime> // pra usar srand (números aleatórios)
#include <locale> // pra liberar todos os caracteres
using namespace std;

//protótipos:
void Tutorial();
void Resets();
void ExibirTab();
void Legendas();
void Jogo();
void EscolherPeca();
void QualPeca();
void PeaoP();
void VingancaP();
void TorreP();
void CavaloP();
void BispoP();
void RainhaP();
void ReiP();
void PeaoC();
void VingancaC();
void TorreC();
void CavaloC();
void BispoC();
void RainhaC();
void ReiC();
void TrocarVez();
void VerificarVencedor();
void GameOver();
void Teste1(); // pode fazer com vários, teste 2, teste3, etc.
void Teste2(); // peão
void Teste3(); //cavalo
void Teste4(); //rei
void Teste5(); //peças CPU
void Teste6(); //gameover
void LimpaArena(); // to usando só no tutorial por enquanto, mas poderia ter em outras funções tbm pra otimizar

//variaveis globais:
bool PecaValida, MovimentoValido;
string UltJog; // mostra qual peça da última jogada
int ultjogil, ultjogic; // registra no tabuleiro as coordenadas inicial da ultima jogada msm q a jogada seja inválida
int ultjogfl, ultjogfc; // registra no tabuleiro as coordenadas final da ultima jogada msm q a jogada seja inválida
int alvol, alvoc; //coordenadas de movimento final, pega linha ce e linha le quando a casa for vazia ou comeu
int le, ce; //linha e coluna escolhidas
string Morto; //guarda a peça morta pra exibir
char JogAt, AdvAt; //guarda o final C ou P. Jogador Atual, Adversário Atual
int vez; //1=player, 2=cpu
int vencedor; // 0=ngm venceu, 1= player venceu, 2=cpu venceu
bool comeu; // marca se comeu ou não. E muda de acordo com a jogada
bool Capturou; // copia o comeu, porém fixo no exibir tab() até mudar de vez
bool vingou; // usa quando o peão atravessa o tabuleiro
string Tab[9][9]; //tabuleiro. 8 posições, ignoro o 0 em todo o projeto, e n fiz de 0 a 8 pq ia ter q rever tudo q eu já traduzi do portugol, sem tempo...
char x; // só pra dar tempo de ler, dps apertar qualquer coisa e seguir. era int, mas botei char, pq tava dando erro loop. Dps descobri q tinha q ser scanf no lugar de cin... mas n vou mudar tudo dnv
char legenda;
int Continue; // maiúsculo pq o minúsculo já é palavra reservada

//-----------------------------------------------------

int main(){

	//setlocale(LC_ALL,""); nada disso funcionaou... sad :(
	setlocale(LC_ALL,"pt_BR.UTF-8");
	//setlocale(LC_ALL, "portuguese");
	//setlocale(LC_ALL, "Portuguese");
	//setlocale(LC_ALL, "Portuguese_Brazil");
	
	srand(time(NULL));//ativa mudança de sementes pra geração de números aleatórios nas outras funções
	string R; //esposta

	do{
		system("cls");
		cout << "Xadrez by Isaque Mendes" << endl;
		do{
			cout << "deseja ver tutorial? (s/n)";
			cin >> R;
			if (R=="s"){
				Tutorial();
			}
			system("cls");
		}while(R!="n"); 
		
		Resets();
		//Teste6(); // use isso pra testar mudando as inicializações do resets() e mantenha todo o jogo normal pra testar o q quiser
		do{
			Jogo();
		}while(vencedor == 0);
	}while(Continue != 2);

	return 0;
}

void Tutorial(){
	
	Resets();
	ExibirTab();
	cout << "Tutorial" << endl;
	cin >> x;
	cout << "esse eh o tabuleiro de 8 linhas e 8 colunas" << endl << endl;
	cin >> x;
	Legendas();
	cout << "espacos vazios representam CASAS BRANCAS." << endl;
	cin >> x;
	cout << "espacos com [ ] representam CASAS PRETAS." << endl << endl;
	cin >> x;
	cout << "suas pecas terminam com P de player." << endl;
	cin >> x;
	cout << "pecas da maquina terminam em C de CPU." << endl << endl;
	cin >> x;
	cout << "digite qualquer coisa pra continuar" << endl;
	cin >> x;
	system("cls");

	cout << "tanto Player quanto CPU usam os mesmos tipos de pecas. Sao elas:" << endl;
	cin >> x;
	cout << "Peao, Torre, Cavalo, Bispo, Rainha e Rei." << endl;
	cin >> x;
	cout << "O objetivo eh proteger o seu Rei e Capturar o Rei da CPU." << endl << endl;
	cin >> x;
	cout << "O passo a passo a seguir eh comum a todas as pecas:" << endl << endl;
	cin >> x;
	cout << "Passo 1: Selecione uma coordenada (linha e coluna) q tenha uma peca sua (terminada em P)." << endl;
	cin >> x;
	cout << "Passo 2: Selecione uma direcao valida (cada peca eh diferente)." << endl;
	cin >> x;
	cout << "Passo 3: Algumas pecas ainda perguntam quantas casas voce deseja andar." << endl;
	cin >> x;
	cout << "observacao: ao capturar uma peca inimiga, sua peca fica no lugar dela." << endl;
	cin >> x;
	cout << "Passo 4: Veja sua ultima jogada e continue para a maquina jogar, e repita o processo." << endl;
	cin >> x;
	cout << "O jogo termina quando um dos Reis morre!" << endl << endl;
	cin >> x;
	cout << "A seguir sera mostrado como jogar com cada peca." << endl;
	cin >> x;
	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//peão ======================================================

	LimpaArena();
	le = 7;
	ce = 5;
	Tab[7][5] = "PP ";
	Tab[6][4] = "TC ";
	Tab[6][6] = "TC ";
	ExibirTab();
	cout << "O Peao pode:" << endl;
	cin >> x;
	cout << "andar 2 casas pra frente, apenas na primeira jogada dele" << endl;
	cin >> x;
	cout << "andar 1 casa para frente, em qualquer jogada" << endl;
	cin >> x;
	cout << "comer peca inimiga nas diagonais esquerda ou direita" << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes do seu Peao:" << endl << endl;
	cin >> x;
   	cout << "Seu PEAO, da linha" << le << ", coluna" << ce << endl;
   	cout << "Selecione uma acao:" << endl;
    cout << "     ^ 2" << endl;
    cout << "     |" << endl;
   	cout << "  q  w  e" << endl;
   	cout << "   \\ | / " << endl;
   	cout << "     +   " << endl << endl;
	cin >> x;

	cout << "Obs: Ao atravessar a arena, seu peao pode ser promovido para Cavalo, Bispo, Torre ou Rainha!" << endl<< endl;
	cin >> x;

	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//torre ======================================================

	LimpaArena();
	le = 5;
	ce = 5;
	Tab[5][5] = "TP ";
	Tab[2][5] = "RC "; // ^ == W 
	Tab[5][2] = "RC "; // <- == A 
	Tab[5][8] = "RC "; // -> == D 
	Tab[8][5] = "RC "; // v == X 
	ExibirTab();
	cout << "A Torre pode:" << endl;
	cin >> x;
	cout << "andar e capturar na horizontal e vertical (pra cima, baixo, esquerda e direita) quantas casas quiser" << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes do sua Torre:" << endl << endl;
	cin >> x;
	cout << "Sua TORRE, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << "     W      " << endl;
	cout << "     ^      " << endl;
	cout << "     |      " << endl;
	cout << "A <- + -> D " << endl;
	cout << "     |      " << endl;
	cout << "     v      " << endl;
	cout << "     X      " << endl << endl;
	cin >> x;

	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//cavalo ======================================================

	LimpaArena();
	le = 5;
	ce = 5;
	Tab[5][5] = "CP ";
	Tab[3][4] = "TC "; // 2
	Tab[3][6] = "TC "; // 3
	Tab[4][3] = "TC "; // Q 
	Tab[4][7] = "TC "; // R 
	Tab[6][3] = "TC "; // A 
	Tab[6][7] = "TC "; // F 
	Tab[7][4] = "TC "; // Z 
	Tab[7][6] = "TC "; // C
	ExibirTab();
	cout << "O Cavalo pode:" << endl;
	cin >> x;
	cout << "andar em L (2 casas e dps 1 (ou ao contrario, tanto faz))" << endl;
	cin >> x;
	cout << "Obs: ele ignora(pula) qualquer peca q esteja no caminho" << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes do seu Cavalo:" << endl << endl;
	cin >> x;
	cout << "Seu CAVALO, da linha" << le << ", coluna"<< ce << endl;
	cout << "Selecione uma direcao:" <<  endl;
	cout << endl;
	cout << "   2_   _3   " << endl;
	cout << "Q    | |    R" << endl;
	cout << " |___| |___| " << endl;
	cout << "  ___ + ___  " << endl;
	cout << " |   | |   | " << endl;
	cout << "A   _| |_   F" << endl;
	cout << "   Z     C   " << endl << endl;
	cin >> x;
	
	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//bispo ======================================================

	LimpaArena();
	le = 5;
	ce = 5;
	Tab[5][5] = "BP ";
	Tab[2][2] = "TC "; // Q 
	Tab[2][8] = "TC "; // E 
	Tab[8][2] = "TC "; // Z 
	Tab[8][8] = "TC "; // C 
	ExibirTab();
	cout << "O Bispo pode:" << endl;
	cin >> x;
	cout << "andar nas diagonais quantas casas quiser." << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes do seu Bispo:" << endl << endl;
	cin >> x;
	cout << "Seu BISPO, da linha" << le << ", coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << "Q       E  " << endl;
	cout << "  \\   /    " << endl;
	cout << "    +      " << endl;
	cout << "  /   \\    " << endl;
	cout << "Z       C  " << endl << endl;
	cin >> x;

	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//rainha ======================================================

	LimpaArena();
	le = 5;
	ce = 5;
	Tab[5][5] = "RP "; 
	Tab[2][2] = "TC "; // Q 
	Tab[2][8] = "TC "; // E 
	Tab[8][2] = "TC "; // Z 
	Tab[8][8] = "TC "; // C 
	Tab[2][5] = "TC "; // ^ == W 
	Tab[5][2] = "TC "; // <- == A w
	Tab[5][8] = "TC "; // -> == D 
	Tab[8][5] = "TC "; // v == X 
	ExibirTab();
	cout << "A Rainha pode:" << endl;
	cin >> x;
	cout << "andar nas horizontais, verticais e diagonais quantas casas quiser (eh a Torre e o Bispo numa unica peca)." << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes da sua Rainha:" << endl << endl;
	cin >> x;
	cout << "Sua RAINHA, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << " Q  W  E  " << endl;
	cout << "  \\ ^ /   " << endl;
	cout << "A < + > D " << endl;
	cout << "  / v \\   " << endl;
	cout << " Z  X  C  " << endl << endl;
	cin >> x;

	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");

	//rei ======================================================

	LimpaArena();
	le = 5;
	ce = 5;
	Tab[5][5] = "rP "; // Q 	
	Tab[4][4] = "CC "; // Q 
	Tab[4][5] = "CC "; // W 
	Tab[4][6] = "CC "; // E 
	Tab[5][4] = "CC "; // A 
	Tab[5][6] = "CC "; // D 
	Tab[6][4] = "CC "; // Z 
	Tab[6][5] = "CC "; // X 
	Tab[6][6] = "CC "; // C <<------
	ExibirTab();
	cout << "O Rei pode:" << endl;
	cin >> x;
	cout << "andar nas horizontais, verticais e diagonais APENAS 1 CASA." << endl << endl;
	cin >> x;

	cout << "Assim aparece as opcoes do seu Rei:" << endl << endl;
	cin >> x;
	cout << "Seu REI, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << " Q  W  E  " << endl;
	cout << "  \\ ^ /   " << endl;
	cout << "A < + > D " << endl;
	cout << "  / v \\   " << endl;
	cout << " Z  X  C  " << endl << endl;
	cin >> x;

	cout << "Fim do tutorial!" << endl;
	cin >> x;
	cout << "digite qualquer coisa pra continuar:" << endl;
	cin >> x;
	system("cls");
}

void Resets(){

	int l,c;
	
	vez=1;
	JogAt = 'P'; // jogador atual = player
	AdvAt = 'C';// adversario atual = cpu
	vencedor = 0; //só pra garantir
	comeu = false; //só pra garantir
	Capturou = false; //só pra garantir
	vingou = false; //só pra garantir
	ultjogil = 0;
	ultjogic = 0;
	ultjogfl = 0;
	ultjogfc = 0;

	//setagens CPU -----------------------
	Tab[1][1] = "TC "; //torre CPU
	Tab[1][2] = "CC "; // cavalo ''
	Tab[1][3] = "BC "; // bispo ''
	Tab[1][4] = "RC "; // Rainha ''
	Tab[1][5] = "rC "; // rei ''
	Tab[1][6] = "BC ";
	Tab[1][7] = "CC ";
	Tab[1][8] = "TC ";

	for (c=1; c<=8; c++){ //peõs
    	Tab[2][c] = "PC "; // peão CPU
	}
	
	for (l=3; l<=6; l++){//arena
    	for (c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparção de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	//setagens Player -----------------------
   	for (c=1; c<=8; c++){
   		Tab[7][c] = "PP "; //peão player
	}

	Tab[8][1] = "TP "; // torre CPU
	Tab[8][2] = "CP "; // cavalo CPU
   	Tab[8][3] = "BP "; // cavalo ''
   	Tab[8][4] = "RP "; // bispo ''
	Tab[8][5] = "rP "; // Rainha ''
   	Tab[8][6] = "BP "; // rei ''
   	Tab[8][7] = "CP ";
   	Tab[8][8] = "TP ";
}

void ExibirTab(){
	
	int c,l; //para PoB (preto ou branco): 1=preto,2=branco
   	bool c2,l2; // linha e colunas, se são par(v) ou impar(f)

	legenda = ' ';

	system("cls");
	//numeração superior
   	cout << "    ";
	for (c=1; c<=8; c++){
		cout << "  " << c;
	}
	//Tabuleiro
	cout << endl;
	for (l=1; l<=8; l++){
    cout << "  " << l << "| ";
    	for (c=1; c<=8; c++){// preenche  tabulueiro. casa bramca é sempre igual (par ou impar), a preta é sempre diferente
        	if (Tab[l][c] == "  "){
	            //verifica se linha é par ou impar
	            if (l%2 == 0){
	               l2 = true; //par
	            }else{
	               l2 = false; // impar
	        	}
	            //verifica se coluna é par ou impar
	            if (c%2 == 0){
	               c2 = true; //par
	            }else{
	               c2 = false; //impar
	        	}
	        	//preencher preto e branco dependendo de par ou ímpar
	            if (l2 xor c2){//xor dá verdadeiro se 2 operadores lógicos forem diferentes e dá falso se forem iguais
	               cout << "[ ]";
	            }else{
	               cout << "   ";
	        	}
    		}else{
        		cout << Tab[l][c];
        	}
        }
	    cout << "|";
	    //relatorios na lateral, pra isso pega o l e escreve junto com a tabela
	    if (l == 3){
	    	cout << "       Ultima jogada:";
		}
	    if (l == 4){
	    	cout << "     " << UltJog << "[" << ultjogil << "," << ultjogic << "]--->[" << ultjogfl << "," << ultjogfc << "]";
		}
	    if ((l == 5) && (Capturou == true)){
	    	cout << "     " << UltJog << "CAPTUROU " << Morto << "!";
		}
	    cout << endl;
   	}
   	cout << endl;	
}

void Legendas(){
	
	cout << endl;
	cout << "                    Legendas:" << endl;
	cout << endl;
	cout << "  PP = Peao do Player   / PC = Peao da CPU" << endl;
	cout << "  TP = Torre do Player  / TC = Torre da CPU" << endl;
	cout << "  CP = Cavalo do Player / CC = Cavalo da CPU" << endl;
	cout << "  BP = Bispo do Player  / BC = Bispo da CPU" << endl;
	cout << "  RP = Rainha do Player / RC = Rainha da CPU" << endl;
	cout << "  rP = Rei do Player    / rC = Rei da CPU" << endl;
	cout << endl;
	cout << "(aperte qualquer coisa para continuar)" << endl;
	cin >> x; // pra sair

}

void Jogo(){

	vingou = false;
	do{
		
		do{
			if (vez == 1){ //só exibe quando for o player
			    do{
			    	ExibirTab();
			    }while (legenda == 'l');
			}
			PecaValida = false;
			EscolherPeca();
			}while (PecaValida == false);
		MovimentoValido = false;
		QualPeca();
		system("cls"); //talvez esteja redundante, mas de toda forma limpa quando for a CPU
	}while (MovimentoValido == false);
	//caso coma a peça
	if ((comeu == true) && (vingou == false)){
		Capturou = true;
		Morto = Tab[alvol][alvoc];
	}else{
		Capturou = false;
	}
	
	//caso geral q não seja vinçanga, atualiza posição
	if (vingou == false){
		Tab[alvol][alvoc] = Tab[le][ce]; // isso vai acontecr sempre q a jogada for válida
		UltJog = Tab[le][ce];
	}
	
	//atualizando pra coordenadas iniciais e final pra exibir toda vez
	ultjogil = le;
	ultjogic = ce;
	ultjogfl = alvol;
	ultjogfc = alvoc;
	
	Tab[le][ce] = "  "; //isso só se torna redundante quando vingança, mas não é um grande problema

	VerificarVencedor();

	if (vencedor == 0){
		if (vez == 1){
			ExibirTab();
			cout << "Vez da CPU" << endl;
			cin >> x;
			system("cls");
		}
		TrocarVez();
	}else{
		do{
	   		GameOver();
		}while ((Continue != 1) && (Continue != 2));
	}

}

void EscolherPeca(){
	if (vez == 1){
		//legenda
		cout << "(Escreva 'L' para ver as legendas, ou qualquer coisa para seguir)";
		cin >> legenda;
		if (legenda == 'l'){
			Legendas();
		}
		//------------
	  	if (legenda != 'l'){ // se apertou qualquer coisa pra seguir
			cout << endl;
			cout << "Sua vez" << endl;
			cout << endl;
			cout << "Escolha uma peca" << endl;
			cout << "Linha (de 1 a 8): ";
			cin >> le;
			cout << "Coluna (de 1 a 8): ";
			cin >> ce;
	  	}
	}else{ // vez da CPU
		for(int c=0; c<1;c++){//n precisaria do for, mas é boa prática
			le = rand()%(8-1+1)+1;
			ce = rand()%(8-1+1)+1;
		}
	}
	//verificar se peça válida
   	if (legenda != 'l'){
    	if ((le < 1) || (le > 8) || (ce < 1) || (ce > 8)){ //se não estiver no tabuleiro
        	PecaValida = false;
        	if (vez == 1){
	            cout << "Nenhuma casa encontrada!" << endl;
	            cin >> x;
    		}
      	}else if (Tab[le][ce] == "  "){ //se estiver vazio
            PecaValida = false;
            if (vez == 1){
				cout << "Casa vazia. Nenhuma peca selecionada!" << endl;
				cin >> x;
        	}
        }else if (Tab[le][ce].at(1) == AdvAt){ // se for do adversario
            PecaValida = false;
        	if (vez == 1){
	          	cout << "Nao eh a sua peca!" << endl;
	          	cin >> x;
		   	}
		}else{
    		PecaValida = true;
	    }
	}

}

void QualPeca(){
	
   	//qualquer peça [se tiver trancado ou a jogada for inválida, volta pro escolher peça()]

   	//player ---------------------------------------------------
   	if (vez == 1){
      	if (Tab[le][ce].at(0) == 'P'){
         	PeaoP();
	   	}else if (Tab[le][ce].at(0) == 'T'){
            TorreP();
    	}else if (Tab[le][ce].at(0) == 'C'){
        	CavaloP();
       	}else if (Tab[le][ce].at(0) == 'B'){
         	BispoP();
        }else if (Tab[le][ce].at(0) == 'R'){
        	RainhaP();
        }else if (Tab[le][ce].at(0) == 'r'){
        	ReiP();
      	}
   	}
   	//CPU ---------------------------------------------------
   	if (vez == 2){
      	if (Tab[le][ce].at(0) == 'P'){
         	PeaoC();
	   	}else if (Tab[le][ce].at(0) == 'T'){
            TorreC();
    	}else if (Tab[le][ce].at(0) == 'C'){
        	CavaloC(); 
       	}else if (Tab[le][ce].at(0) == 'B'){
         	BispoC();
        }else if (Tab[le][ce].at(0) == 'R'){
        	RainhaC();
        }else if (Tab[le][ce].at(0) == 'r'){
        	ReiC();
      	}
   	}
}

//peças player-----------------------------------------

void PeaoP(){
	char R; //resposta
	
   	cout << endl;
   	cout << "Seu PEAO, da linha" << le << ", coluna" << ce << endl;
   	cout << "Selecione uma acao:" << endl;
   	if (le == 7) { //caso seja primeiro passo do peão
      cout << "     ^ 2" << endl;
      cout << "     |" << endl;
   	}
   	cout << "  q  w  e" << endl;
   	cout << "   \\ | / " << endl;
   	cout << "     +   " << endl;

   	cin >> R;

   	//andar 1 casa------------------------------------
   	if (R == 'w') { // caso normal
		if (Tab[le-1][ce] == "  "){//caso vazio, anda
			MovimentoValido = true;
			comeu = false;
			Tab[le-1][ce] = Tab[le][ce];
			alvol = le-1;
			alvoc = ce;
      	}else{ // caso bloqueado
	   		MovimentoValido = false;
	       	comeu = false;
	       	cout << "Nao tem pra ONDE andar." << endl;
	       	cin >> x;
    	}
	}else if ((R == '2') && (le == 7)){ //andar 2 casas-----------------------------------------
        if (Tab[le-1][ce] != "  ") {//caso tente pular
            MovimentoValido = false;
            comeu = false;
            cout << "Nao pode PULAR casa." << endl;
            cin >> x;
     	}else if (Tab[le-2][ce] != "  "){ // caso bloqueado
          	MovimentoValido = false;
           	comeu = false;
           	cout << "Ja tem uma peca nessa casa." << endl;
           	cin >> x;
        }else{//caso normal
           	MovimentoValido = true;
           	comeu = false;
           	Tab[le-2][ce] = Tab[le][ce];
           	alvol = le-2;
           	alvoc = ce;
        }
    }else if (R == 'q'){ //comer esquerda---------------------------------
        if (ce-1 < 1) { //caso parede
			MovimentoValido = false;
			comeu = false;
			cout << "Nao tem pra ONDE comer" << endl;
			cin >> x;
        }else if (Tab[le-1][ce-1].at(1) == AdvAt) { //caso coma
			MovimentoValido = true;
          	comeu = true;
          	alvol = le-1;
          	alvoc = ce-1;
		}else{ // não comeu e não parede
          	MovimentoValido = false;
          	comeu = false;
          	cout <<"Nao tem QUEM comer." << endl;
          	cin >> x;
        }
    }else if (R == 'e') { //comer direita--------------------------------------
       	if (ce+1 > 8) { // caso parede
          	MovimentoValido = false;
          	comeu = false;
          	cout << "Nao tem pra ONDE comer." << endl;
          	cin >> x;
       	}else if (Tab[le-1][ce+1].at(1) == AdvAt) { //caso coma
            MovimentoValido = true;
            comeu = true;
            alvol = le-1;
        	alvoc = ce+1;
        }else {//não comeu e não parede
            MovimentoValido = false;
            comeu = false;
            cout << "Nao tem QUEM comer."  << endl;
            cin >> x;
        }
    }else{ // se não escolher nenhuma opção válida------------------------------------------
    	MovimentoValido = false;
        comeu = false;
        cout << "Opcao invalida" << endl;
        cin >> x;
    }

	//se atravessar o tabuleiro
   	if ((MovimentoValido == true) && (alvol == 1)) {
      	VingancaP();
   	}	
	
}

void VingancaP(){
	int V; //contador e vingança

	Tab[le][ce] = "  ";
	vingou = true;
	UltJog = "PP ";

	if (comeu == true){
		Morto = Tab[alvol][alvoc];
	}
	
	do{
		ExibirTab();
		cout << "Parabens! Vc conseguiu cruzar a arena!" << endl;
		cout << "Escolha uma peca para trocar!" << endl;
		cout << "1:Cavalo; 2:Bispo; 3:Torre; 4:Rainha" << endl;
		V = 0; //xxx evitar lixo, talvez nem precise, mas vai saber...
		scanf("%d",&V); // xxx isso previne erro de loopar entrada de char quando pede int, botei aki, poderia seria ridículo travar tudo na vingança kk
		switch (V){
			case 1:
				system("cls");
				Tab[alvol][alvoc] = "CP ";
				cout << "Seu Peao da casa [" << alvol << "," << alvoc << "] foi promovido para Cavalo!" << endl;
				cin >> x; 
				break;
			case 2:
				system("cls");
				Tab[alvol][alvoc] = "BP ";
				cout << "Seu Peao da casa [" << alvol << "," << alvoc << "] foi promovido para Bispo!" << endl;
				cin >> x;
				break;
			case 3:
				system("cls");
				Tab[alvol][alvoc] = "TP ";
				cout << "Seu Peao da casa [" << alvol << "," << alvoc << "] foi promovido para Torre!" << endl;
				cin >> x;
				break;
			case 4:
				system("cls");
				Tab[alvol][alvoc] = "RP ";
				cout <<  "Seu Peao da casa ["<< alvol << "," << alvoc <<"] foi promovido para Rainha!" << endl;
				cin >> x;
				break;
			default:
				cout <<  "Resposta Invalida. Tente novamente" << endl;
				cin >> x;
				break;
		}
	}while ((V < 1) || (V > 4));
}

void TorreP(){
	
	char R; // resposta
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int TryIn, TryOut; // inicio e fim do teste
	
	cout << endl;
	cout << "Sua TORRE, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << "     W      " << endl;
	cout << "     ^      " << endl;
	cout << "     |      " << endl;
	cout << "A <- + -> D " << endl;
	cout << "     |      " << endl;
	cout << "     v      " << endl;
	cout << "     X      " << endl;
	cin >>  R;
	
	if  (R == 'w') { //cima---------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if  ((le-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le-casas][ce].at(1) == JogAt) { //caso sua peça
				MovimentoValido = false;
				comeu = false;
				cout << "Nao pode comer a PROPRIA PECA." << endl;
				cin >> x;
		}else{ // se  não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le-1;
			TryOut = (le-casas)+1;
			MovimentoValido = true;
			//procedimento padrão
			for (TryIn=TryIn; TryIn>=TryOut; TryIn--) {
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					comeu = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) { 
				comeu = false;
				alvol = le-casas;
				alvoc = ce;
				if  (Tab[le-casas][ce] ==  "  ") { //caso normal
					Tab[le-casas][ce] = Tab[le][ce];
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if  (R == 'a') { // esquerda -------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if  ((ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout <<  "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se  não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce-1;
			TryOut = (ce-casas)+1;
			MovimentoValido = true;			
			//procediemnto padrão
			for (TryIn=TryIn; TryIn>=TryOut; TryIn--) {
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					comeu = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) {
				comeu = false;
				alvol = le;
				alvoc = ce-casas;
				if (Tab[le][ce-casas] ==  "  ") { //caso normal
					Tab[le][ce-casas] = Tab[le][ce];
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'd') { // direita ----------------------------------------------
		cout <<  "Quantas Casas?" << endl;
		cin >> casas;
		if ((ce+casas > 8) || (casas == 0)) { 	//caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout <<  "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce+1;
			TryOut = (ce+casas)-1;
			MovimentoValido = true;
			//procediemnto padrão
			for (TryIn=TryIn; TryIn <=TryOut; TryIn++) {
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					comeu = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}	
			if  (MovimentoValido == true) {
				comeu = false;
				alvol = le;
				alvoc = ce+casas;
				if (Tab[le][ce+casas] == "  ") { //caso normal
					Tab[le][ce+casas] = Tab[le][ce];
				}else{
					comeu = true; //caso coma
				}
			}
		}
	}else if  (R == 'x') { // baixo --------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if  ((le+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le+casas][ce].at(1) ==  JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le+1;
			TryOut = (le+casas)-1;
			MovimentoValido = true;
			//procediemnto padrão
			for (TryIn=TryIn; TryIn<=TryOut; TryIn++) {
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					comeu = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if  (MovimentoValido == true) {
				comeu = false;
				alvol = le+casas;
				alvoc = ce;
				if  (Tab[le+casas][ce] ==  "  ") { //caso normal
					Tab[le+casas][ce] = Tab[le][ce];
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else{
		cout << "Opcao invalida" << endl;
		cin >> x;
		comeu = false;
	}
}

void CavaloP(){
	char R; // resposta
	
	cout << endl;
	cout << "Seu CAVALO, da linha" << le << ", coluna"<< ce << endl;
	cout << "Selecione uma direcao:" <<  endl;
	cout << endl;
	cout << "   2_   _3   " << endl;
	cout << "Q    | |    R" << endl;
	cout << " |___| |___| " << endl;
	cout << "  ___ + ___  " << endl;
	cout << " |   | |   | " << endl;
	cout << "A   _| |_   F" << endl;
	cout << "   Z     C   " << endl;
	cin >> R;
   
	if (R == '2'){ //---------------------------------------------------------
		if  ((le-2 < 1) || (ce-1 < 1)){ //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le-2][ce-1].at(1) == JogAt){ //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le-2;
			alvoc = ce-1;
			if (Tab[le-2][ce-1] == "  "){ //caso normal
				Tab[le-2][ce-1] == Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == '3'){//---------------------------------------------------------
		if  ((le-2 < 1) || (ce+1 > 8)){ //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le-2][ce+1].at(1) == JogAt){ //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le-2;
			alvoc = ce+1;
			if (Tab[le-2][ce+1] == "  "){ //caso normal
				Tab[le-2][ce+1] == Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'q') { //---------------------------------------------------------
		if ((le-1 < 1) || (ce-2 < 1)){ //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le-1][ce-2].at(1) == JogAt){ //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce-2;
			if (Tab[le-1][ce-2] == "  "){//caso normal
				Tab[le-1][ce-2] = Tab[le][ce]; //acho q isso ta redundante, pq lá em cima ele já substitui lece pra alvo em Tab
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'r'){ //--------------------------------------------------------- 
		if  ((le-1 < 1) || (ce+2 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if  (Tab[le-1][ce+2].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce+2;
			if (Tab[le-1][ce+2] == "  ") { //caso normal
				Tab[le-1][ce+2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'a'){ //---------------------------------------------------------
		if ((le+1 > 8) || (ce-2 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le+1][ce-2].at(1) == JogAt){ //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce-2;
			if (Tab[le+1][ce-2] == "  ") { //caso normal
				Tab[le+1][ce-2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'f') { //---------------------------------------------------------
		if  ((le+1 > 8) || (ce+2 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout <<  "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le+1][ce+2].at(1) == JogAt){ //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce+2;
			if (Tab[le+1][ce+2] == "  ") { //caso normal
				Tab[le+1][ce+2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'z') { //---------------------------------------------------------
		if  ((le+2 > 8) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le+2][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le+2;
			alvoc = ce-1;
			if (Tab[le+2][ce-1] == "  ") { //caso normal
				Tab[le+2][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'c') { //---------------------------------------------------------
		if  ((le+2 > 8) || (ce+1 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le+2][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{
			MovimentoValido = true;
			alvol = le+2;
			alvoc = ce+1;
			if (Tab[le+2][ce+1] == "  ") { //caso normal
				Tab[le+2][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else{//---------------------------------------------------------
		cout << "Opcao invalida" << endl;
		cin >> x;
		comeu = false;
	}
}

void BispoP(){
	
	char R;
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int lti; // linha teste inicial
	int ltf; // linha teste final
	int cti; // coluna teste inicial

	cout << endl;
	cout << "Seu BISPO, da linha" << le << ", coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << "Q       E  " << endl;
	cout << "  \\   /    " << endl;
	cout << "    +      " << endl;
	cout << "  /   \\    " << endl;
	cout << "Z       C  " << endl;
	cin >> R;
	
	
	if (R == 'q') { //------------------------------------------------------------
		cout <<  "Quantas Casas?";
		cin >> casas;
		//caso fora
		if ((le-casas < 1) || (ce-casas < 1) || (casas == 0)) {
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le-casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce-1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			//procedimento padrão
			for (lti=lti; lti>=ltf; lti--){
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
				cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce-casas;
				if (Tab[le-casas][ce-casas] ==  "  ") { //caso normal
					Tab[le-casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'e') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;;
		cin >> casas;
		if ((le-casas < 1) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le-casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
			}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce+1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			//procediemnto padrão
			for (lti=lti; lti>=ltf; lti--){
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
				cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce+casas;
				if (Tab[le-casas][ce+casas] ==  "  ") { //caso normal
					Tab[le-casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	} else if (R == 'z') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le+casas > 8) || (ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le+casas][ce-casas].at(1) == JogAt) { //caso sua peça
				MovimentoValido = false;
				comeu = false;
				cout << "Nao pode comer a PROPRIA PECA." << endl;
				cin >> x;
			}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
				lti = le+1;
				cti = ce-1;
				ltf = (le+casas)-1;
				MovimentoValido = true;
			//procediemnto padrão
			for (lti=lti; lti<=ltf; lti++){
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
				cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce-casas;
				if (Tab[le+casas][ce-casas] ==  "  ") { //caso normal
					Tab[le+casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
				comeu = true;
				}
			}
		}
	}else if (R == 'c') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le+casas > 8) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le+casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce+1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			//procediemnto padrão
			for (lti=lti; lti<=ltf; lti++){
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
				cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce+casas;
				if (Tab[le+casas][ce+casas] ==  "  ") { //caso normal
					Tab[le+casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else{ //------------------------------------------------------------
		cout << "Opcao invalida" << endl;
		cin >> x;
		comeu = false;
	}
}

void RainhaP(){

	char R;
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int TryIn; // inicio do teste
	int TryOut; // final do teste
	int lti; // linha teste inicial
	int ltf; // linha teste final
	int cti; // coluna teste inicial

	cout << endl;
	cout << "Sua RAINHA, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << " Q  W  E  " << endl;
	cout << "  \\ ^ /   " << endl;
	cout << "A < + > D " << endl;
	cout << "  / v \\   " << endl;
	cout << " Z  X  C  " << endl;
	cin >> R;

	if (R == 'q') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le-casas < 1)||(ce-casas < 1)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le-casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce-1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti;  lti >= ltf; lti--) { //procedimento padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce-casas;
				if (Tab[le-casas][ce-casas] ==  "  ") { //caso normal
					Tab[le-casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
    }else if (R == 'w') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le-casas < 1)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le-casas][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le-1;
			TryOut = (le-casas)+1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn >= TryOut; TryIn--) {//procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce;
				if (Tab[le-casas][ce] ==  "  ") { //caso normal
					Tab[le-casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'e') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le-casas < 1)||(ce+casas > 8)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le-casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce+1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti;  lti >= ltf; lti--) { //procedimento padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
				cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce+casas;
				if (Tab[le-casas][ce+casas] ==  "  ") { 	//caso normal
				Tab[le-casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'a') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((ce-casas < 1)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if (Tab[le][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce-1;
			TryOut = (ce-casas)+1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn >= TryOut; TryIn--) {//procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce-casas;
				if (Tab[le][ce-casas] ==  "  ") { //caso normal
					Tab[le][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'd') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((ce+casas > 8)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce+1;
			TryOut = (ce+casas)-1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn <= TryOut; TryIn++) {//procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce+casas;
				if (Tab[le][ce+casas] ==  "  ") {	//caso normal
				Tab[le][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'z') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le+casas > 8)||(ce-casas < 1)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le+casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce-1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti;  lti <= ltf; lti++) { //procedimento padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce-casas;
				if (Tab[le+casas][ce-casas] == "  ") { //caso normal
					Tab[le+casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'x') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le+casas > 8)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le+casas][ce].at(1) ==  JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le+1;
			TryOut = (le+casas)-1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn <= TryOut; TryIn++) {//procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce;
				if (Tab[le+casas][ce] ==  "  ") { //caso normal
					Tab[le+casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 'c') { //------------------------------------------------------------
		cout << "Quantas Casas?" << endl;
		cin >> casas;
		if ((le+casas > 8)||(ce+casas > 8)||(casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >> x;
		}else if(Tab[le+casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >> x;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce+1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti;  lti <= ltf; lti++) { //procedimento padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					cout << "Nao pode PULAR pecas." << endl;
					cin >> x;
					break;
				}
			cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce+casas;
				if (Tab[le+casas][ce+casas] == "  ") { //caso normal
					Tab[le+casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else{//------------------------------------------------------------
		cout << "Opcao invalida" << endl;
		cin >> x;
		comeu = false;
	}
}

void ReiP() {

	char R;

	cout << endl;
	cout << "Seu REI, da linha" << le << " coluna" << ce << endl;
	cout << "Selecione uma direcao:" << endl;
	cout << endl;
	cout << " Q  W  E  " << endl;
	cout << "  \\ ^ /   " << endl;
	cout << "A < + > D " << endl;
	cout << "  / v \\   " << endl;
	cout << " Z  X  C  " << endl;
	cin >> R;

	if (R == 'q') { //------------------------------------------------------------
		if ((le-1 < 1) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le-1][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce-1;
			if (Tab[le-1][ce-1] == "  ") { //caso normal
				Tab[le-1][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'w') { //cima------------------------------------------------------------
		if (le-1 < 1) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le-1][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce;
			if (Tab[le-1][ce] == "  ") { //caso normal
				Tab[le-1][ce] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'e') { //------------------------------------------------------------
		if ((le-1 < 1) || (ce+1 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le-1][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce+1;
			if (Tab[le-1][ce+1] == "  ") { //caso normal
				Tab[le-1][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'a') { //esquerda ------------------------------------------------------------
		if (ce-1 < 1) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le;
			alvoc = ce-1;
			if (Tab[le][ce-1] == "  ") { //caso normal
				Tab[le][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'd') { //direita ------------------------------------------------------------
		if  (ce+1 > 8) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le;
			alvoc = ce+1;
			if (Tab[le][ce+1] == "  ") { //caso normal
				Tab[le][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'z') { //------------------------------------------------------------
		if ((le+1 > 8) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le+1][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce-1;
			if (Tab[le+1][ce-1] == "  ") { //caso normal
				Tab[le+1][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}
	else if (R == 'x') { //baixo ------------------------------------------------------------
		if  (le+1 > 8) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le+1][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce;
			if (Tab[le+1][ce] == "  ") { //caso normal
				Tab[le+1][ce] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 'c') { //------------------------------------------------------------
		if ((le+1 > 8) || (ce+1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode jogar FORA do tabuleiro, nem ficar PARADO." << endl;
			cin >>  x;
		}else if (Tab[le+1][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
			cout << "Nao pode comer a PROPRIA PECA." << endl;
			cin >>  x;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce+1;
			if (Tab[le+1][ce+1] == "  ") { //caso normal
				Tab[le+1][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else{ //------------------------------------------------------------
		cout << "Opcao invalida" << endl;
		cin >>  x;
		comeu = false;
	}
}

//peças CPU-----------------------------------------

void PeaoC(){

	int R;

	// ("     ^2     ")
	// ("     |      ")
	// ("  3  ^1  4  ")
	// ("   \ | /    ")
	// ("     +      ")

	for(int c=0; c<1; c++){
		R = rand()%(4-1+1)+1;
	}

	if (R == 1) { //andar 1 casa------------------------------------
		if (Tab[le+1][ce] == "  ") {
			MovimentoValido = true;
			comeu = false;
			Tab[le+1][ce] = Tab[le][ce];
			alvol = le+1;
			alvoc = ce;
		}else{
			MovimentoValido = false;
		}
	}else if ((R == 2) && (le == 2)) { //andar 2 casas-----------------------------------------
		if (Tab[le+1][ce] != "  ") { //caso tente pular
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+2][ce] != "  ") { // caso bloqueado
			MovimentoValido = false;
			comeu = false;
		}else{ //caso normal
			MovimentoValido = true;
			comeu = false;
			Tab[le+2][ce] = Tab[le][ce];
			alvol = le+2;
			alvoc = ce;
		}
	}else if (R == 3) { //comer esquerda---------------------------------
		if (ce-1 < 1) { //caso parede
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+1][ce-1].at(1) == AdvAt) { //caso coma
			MovimentoValido = true;
			comeu = true;
			alvol = le+1;
			alvoc = ce-1;
		}else{ // não comeu e não parede
			MovimentoValido = false;
			comeu = true;
		}
	}else if (R == 4) { //comer direita--------------------------------------
		if (ce+1 > 8) { // caso parede
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce+1].at(1) == AdvAt) { // caso coma
			MovimentoValido = true;
			comeu = true;
			alvol = le+1;
			alvoc = ce+1;
		}else{ //--------------------------------
			MovimentoValido = false;
			comeu = true;
		}
	}

	if ((MovimentoValido == true) && (alvol == 8)) {
		VingancaC();
	}

}

void VingancaC(){

	int V; // V de vingança hehe'

	Tab[le][ce] = "  ";
	vingou = true;
	UltJog = "PC ";

	if (comeu == true) {
		Morto = Tab[alvol][alvoc];
 	}

	for(int c=0; c<1; c++){
		V = rand()%(4-1+1)+1;
	}

	//poderia ser um case tbm
	switch (V){
		case 1:
			Tab[alvol][alvoc] = "CC ";
			cout << "Peao da CPU da casa [" << alvol << "," << alvoc << "] foi promovido para Cavalo!" << endl;
			cin >> x;// embora seja CPU, o player aperta pra prosseguir
			break;
		case 2:
			Tab[alvol][alvoc] = "BC ";
			cout << "Peao da CPU da casa [" << alvol << "," << alvoc << "] foi promovido para Bispo!" << endl;
			cin >> x;
			break;
		case 3:
			Tab[alvol][alvoc] = "TC ";
			cout << "Peao da CPU da casa [" << alvol << "," << alvoc << "] foi promovido para Torre!" << endl;
			cin >> x;
			break;
		case 4:
			Tab[alvol][alvoc] = "RC ";
			cout << "Peao da CPU da casa [" << alvol << "," << alvoc << "] foi promovido para Rainha!" << endl;
			cin >> x;
			break;
	}

}

void TorreC(){

	int R; // resposta
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int TryIn, TryOut; // inicio e fim do teste

	// ("     1      ")
	// ("     ^      ")
	// ("     |      ")
	// ("2 <- + -> 3 ")
	// ("     |      ")
	// ("     v      ")
	// ("     4      ")

	for(int c=0; c<1;c++){
		R = rand()%(4-1+1)+1;
	}

	if (R == 1) { //cima---------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le-1;
			TryOut = (le-casas)+1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn >= TryOut; TryIn--){ //procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce;
				if (Tab[le-casas][ce] ==  "  ") { //caso normal
					Tab[le-casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 2) { // esquerda -------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Eele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce-1;
			TryOut = (ce-casas)+1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn >= TryOut; TryIn--){ //procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce-casas;
				if (Tab[le][ce-casas] ==  "  ") { //caso padrão
					Tab[le][ce-casas] = Tab[le][ce];
						comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 3) { // direita ----------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce+1;
			TryOut = (ce+casas)-1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn <= TryOut; TryIn++){ //procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce+casas;
				if (Tab[le][ce+casas] ==  "  ") { //caso normal
					Tab[le][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 4) { // baixo --------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce].at(1) ==  JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le+1;
			TryOut = (le+casas)-1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn <= TryOut; TryIn++){ //procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce;
				if (Tab[le+casas][ce] ==  "  ") { //caso normal
					Tab[le+casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}

}

void CavaloC(){

	int R;

	// ("   1_   _2   ")
	// ("3    | |    4")
	// (" |___| |___| ")
	// ("  ___ + ___  ")
	// (" |   | |   | ")
	// ("5   _| |_   6")
	// ("   7     8   ")

	for(int c=0; c<1;c++){
		R = rand()%(8-1+1)+1;
	}

	if (R == 1) { //---------------------------------------------------------
		if ((le-2 < 1) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-2][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-2;
			alvoc = ce-1;
			if (Tab[le-2][ce-1] == "  ") { //caso normal
				Tab[le-2][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 2) { //---------------------------------------------------------
		if ((le-2 < 1) || (ce+1 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-2][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-2;
			alvoc = ce+1;
			if (Tab[le-2][ce+1] == "  ") { //caso normal
				Tab[le-2][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 3) { //---------------------------------------------------------
		if ((le-1 < 1) || (ce-2 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-1][ce-2].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce-2;
			if (Tab[le-1][ce-2] == "  ") { //caso normal
				Tab[le-1][ce-2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 4) { //---------------------------------------------------------
		if ((le-1 < 1) || (ce+2 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-1][ce+2].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce+2;
			if (Tab[le-1][ce+2] == "  ") { //caso normal
				Tab[le-1][ce+2] = Tab[le][ce];
				comeu = false;
			}else {//caso coma
				comeu = true;
			}
		}
	} else//---------------------------------------------------------
	if (R == 5) {//caso fora
		if ((le+1 > 8) || (ce-2 < 1)) {
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce-2].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce-2;
			if (Tab[le+1][ce-2] == "  ") { //caso normal
				Tab[le+1][ce-2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 6) { //---------------------------------------------------------
		if ((le+1 > 8) || (ce+2 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce+2].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce+2;
			if (Tab[le+1][ce+2] == "  ") { //caso normal
				Tab[le+1][ce+2] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 7) { //---------------------------------------------------------
		if ((le+2 > 8) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+2][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+2;
			alvoc = ce-1;
			if (Tab[le+2][ce-1] == "  ") { //caso normal
				Tab[le+2][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 8) { //---------------------------------------------------------
		if ((le+2 > 8) || (ce+1 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+2][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+2;
			alvoc = ce+1;
			if (Tab[le+2][ce+1] == "  ") { //caso normal
				Tab[le+2][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}
}

void BispoC(){

	int R;
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int lti; // linha teste inicial
	int ltf; // linha teste final
	int cti; // coluna teste inicial

	// ("1       2  ")
	// ("  \   /    ")
	// ("    +      ")
	// ("  /   \    ")
	// ("3       4  ")

	for(int c=0; c<1;c++){
		R = rand()%(4-1+1)+1;
	}


	if (R == 1) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce-1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti; lti >= ltf; lti--) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
				cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce-casas;
				if (Tab[le-casas][ce-casas] ==  "  ") { //caso normal
					Tab[le-casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 2) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce+1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti; lti >= ltf; lti--) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
				cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce+casas;
				if (Tab[le-casas][ce+casas] ==  "  ") { //caso normal
					Tab[le-casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 3) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce-1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti; lti <= ltf; lti++) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
				cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce-casas;
				if (Tab[le+casas][ce-casas] ==  "  ") { //caso normal
					Tab[le+casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 4) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce+1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti; lti <= ltf; lti++) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
				cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce+casas;
				if (Tab[le+casas][ce+casas] ==  "  ") { //caso normal
					Tab[le+casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}

}

void RainhaC() {

	int R;
	int casas; // poderia ser o R, mas só pra facilitar a leitura
	int TryIn; // inicio do teste
	int TryOut; // final do teste
	int lti; // linha teste inicial
	int ltf; // linha teste final
	int cti; // coluna teste inicial

	// (" 1  2  3  ")
	// ("  \ ^ /   ")
	// ("4 < + > 5 ")
	// ("  / v \   ")
	// (" 6  7  8  ")
	for(int c=0; c<1;c++){
		R = rand()%(8-1+1)+1;
	}

	if (R == 1) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{// se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce-1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti; lti >= ltf; lti--) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
			cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce-casas;
				if (Tab[le-casas][ce-casas] ==  "  ") { //caso normal
					Tab[le-casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}
	else if (R == 2) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le-1;
			TryOut = (le-casas)+1;
			MovimentoValido = true;
			for (TryIn = TryIn; TryIn >= TryOut; TryIn--) { //procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso normal
				alvol = le-casas;
				alvoc = ce;
				if (Tab[le-casas][ce] ==  "  ") { //caso normal
					Tab[le-casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 3) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le-casas < 1) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le-casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le-1;
			cti = ce+1;
			ltf = (le-casas)+1;
			MovimentoValido = true;
			for (lti = lti; lti >= ltf; lti--) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
			cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le-casas;
				alvoc = ce+casas;
				if (Tab[le-casas][ce+casas] ==  "  ") { //caso normal
					Tab[le-casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 4) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce-1;
			TryOut = (ce-casas)+1;
			MovimentoValido = true;
			for (TryIn =TryIn; TryIn >= TryOut; TryIn--) { //procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce-casas;
				if (Tab[le][ce-casas] ==  "  ") { //caso normal
					Tab[le][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 5) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = ce+1;
			TryOut = (ce+casas)-1;
			MovimentoValido = true;
			for (TryIn =TryIn; TryIn <= TryOut; TryIn++) { //procediemnto padrão
				if (Tab[le][TryIn] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le;
				alvoc = ce+casas;
				if (Tab[le][ce+casas] ==  "  ") { //caso normal
					Tab[le][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 6) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (ce-casas < 1) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce-casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // se não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce-1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti; lti <= ltf; lti++) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
			cti = cti-1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce-casas;
				if (Tab[le+casas][ce-casas] == "  ") { //caso normal
					Tab[le+casas][ce-casas] = Tab[le][ce];
					comeu = false;
				}else{//caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 7) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce].at(1) ==  JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			TryIn = le+1;
			TryOut = (le+casas)-1;
			MovimentoValido = true;
			for (TryIn =TryIn; TryIn <= TryOut; TryIn++) { //procediemnto padrão
				if (Tab[TryIn][ce] != "  ") {
					MovimentoValido = false;
					break;
				}
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce;
				if (Tab[le+casas][ce] ==  "  ") { //caso normal
					Tab[le+casas][ce] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}else if (R == 8) { //------------------------------------------------------------
		for(int c=0; c<1;c++){
			casas = rand()%(7-1+1)+1;
		}
		if ((le+casas > 8) || (ce+casas > 8) || (casas == 0)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if(Tab[le+casas][ce+casas].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{ // if não for fora, contar as casas anteriores. Ele faz isso tanto pra andar normal, quanto pra comer
			lti = le+1;
			cti = ce+1;
			ltf = (le+casas)-1;
			MovimentoValido = true;
			for (lti = lti; lti <= ltf; lti++) { //procediemnto padrão
				if (Tab[lti][cti] != "  ") {
					MovimentoValido = false;
					break;
				}
			cti = cti+1;
			}
			if (MovimentoValido == true) { //caso válido
				alvol = le+casas;
				alvoc = ce+casas;
				if (Tab[le+casas][ce+casas] == "  ") { //caso normal
					Tab[le+casas][ce+casas] = Tab[le][ce];
					comeu = false;
				}else{ //caso coma
					comeu = true;
				}
			}
		}
	}

}

void ReiC(){

	int R;

	// (" 1  2  3  ")
	// ("  \ ^ /   ")
	// ("4 < + > 5 ")
	// ("  / v \   ")
	// (" 6  7  8  ")
	for(int c=0; c<1;c++){
		R = rand()%(8-1+1)+1;
	}

	if (R == 1) { //------------------------------------------------------------
		if ((le-1 < 1) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-1][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce-1;
			if (Tab[le-1][ce-1] == "  ") { //caso normal
				Tab[le-1][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 2) { //cima------------------------------------------------------------
		if (le-1 < 1) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-1][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce;
			if (Tab[le-1][ce] == "  ") { //caso normal
				Tab[le-1][ce] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 3) { //------------------------------------------------------------
		if ((le-1 < 1) || (ce+1 > 8)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le-1][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le-1;
			alvoc = ce+1;
			if (Tab[le-1][ce+1] == "  ") { //caso normal
				Tab[le-1][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 4) { //esquerda ------------------------------------------------------------
		if (ce-1 < 1) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le;
			alvoc = ce-1;
			if (Tab[le][ce-1] == "  ") { //caso normal
				Tab[le][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 5) { //direita ------------------------------------------------------------
		if  (ce+1 > 8) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le;
			alvoc = ce+1;
			if (Tab[le][ce+1] == "  ") { //caso normal
				Tab[le][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 6) { //------------------------------------------------------------
		if ((le+1 > 8) || (ce-1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce-1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce-1;
			if (Tab[le+1][ce-1] == "  ") { //caso normal
				Tab[le+1][ce-1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 7) { //baixo ------------------------------------------------------------
		if  (le+1 > 8) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce;
			if (Tab[le+1][ce] == "  ") { //caso normal
				Tab[le+1][ce] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}else if (R == 8) { //------------------------------------------------------------
		if ((le+1 > 8) || (ce+1 < 1)) { //caso fora
			MovimentoValido = false;
			comeu = false;
		}else if (Tab[le+1][ce+1].at(1) == JogAt) { //caso sua peça
			MovimentoValido = false;
			comeu = false;
		}else{
			MovimentoValido = true;
			alvol = le+1;
			alvoc = ce+1;
			if (Tab[le+1][ce+1] == "  ") { //caso normal
				Tab[le+1][ce+1] = Tab[le][ce];
				comeu = false;
			}else{ //caso coma
				comeu = true;
			}
		}
	}
}

void TrocarVez(){

	if (vez == 1) { //caso player
		vez = 2;
		JogAt = 'C';
		AdvAt = 'P';
	}else{ //caso cpu
		vez = 1;
		JogAt = 'P';
		AdvAt = 'C';
 	}

}

void VerificarVencedor(){

	int l,c;
	bool rP, rC; //rei dos 2 se ta vivo

	//rodar o tab todo e procurar se NÃO tiver rei do player a cpu ganhou, e vice versa

	//ve se o rei do player ta vivo
	for (l=1; l<=8; l++) {
		for (c=1; c<=8; c++) {
			if (Tab[l][c] == "rP ") {
				rP = true;
				break;
			}else{
				rP = false;
			}
		}
		if (Tab[l][c] == "rP ") {
			rP = true;
			break;
		}
	}
	//ve se o rei da cpu ta vivo
	for (l=1; l <=8; l++) {
		for (c=1; c<=8; c++) {
			if (Tab[l][c] == "rC ") {
				rC = true;
				break;
			}else{
				rC = false;
			}
		}
		if (Tab[l][c] == "rC ") {
			rC = true;
			break;
		}
	}

	//resultados
	if ((rP == true) && (rC == false)) { //player venceu
		vencedor = 1;
	}else if ((rP == false) && (rC == true)) { //cpu venceu
		vencedor = 2;
	}else{ // ninguém vencem ainda
		vencedor = 0;
	}

}

void GameOver(){

	ExibirTab();
	if (vencedor == 1) { //caso player
		cout << "=====================================================" << endl;
		cout << "                       Vc venceu!" << endl;
		cout << "=====================================================" << endl;
	}else{ //caso cpu
		cout << "=====================================================" << endl;
		cout << "                       Vc perdeu!" << endl;
		cout << "=====================================================" << endl;
	}

	cout << "1: Jogar Novamente" << endl;
	cout << "2: Sair" << endl;
	cin >> Continue;

}

void Teste1(){

	//usando pra peças q andam mt
	vez = 1;
	JogAt = 'P';
	AdvAt = 'C';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparção de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	Tab[5][5] = "TP ";
	
	//diagonais
	Tab[3][3] = "RC "; // Q 
	Tab[3][7] = "RC "; // E 
	Tab[7][3] = "RC "; // Z 
	Tab[7][7] = "RC "; // C <<------
	
	
	//horizontal e vertical
	Tab[3][5] = "RC "; // ^ == W 
	Tab[5][3] = "RC "; // <- == A 
	Tab[5][7] = "RC "; // -> == D 
	Tab[7][5] = "RC "; // v == X 
	

}

void Teste2(){

	//testando peão
	vez = 1;
	JogAt = 'P';
	AdvAt = 'C';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	Tab[7][2] = "PP ";

	//inimigos
	Tab[6][4] = "CC ";
	Tab[5][5] = "CC ";
	Tab[6][6] = "CC ";

}

void Teste3(){

	//testando cavalo
	vez = 1;
	JogAt = 'P';
	AdvAt = 'C';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	Tab[5][5] = "CP ";

	//inimigos
	Tab[3][4] = "CC "; // 2
	Tab[3][6] = "CC "; // 3
	Tab[4][3] = "CC "; // Q 
	Tab[4][7] = "CC "; // R 
	Tab[6][3] = "CC "; // A 
	Tab[6][7] = "CC "; // F 
	Tab[7][4] = "CC "; // Z 
	Tab[7][6] = "CC "; // C <<------
}

void Teste4(){

	//testando rei
	vez = 1;
	JogAt = 'P';
	AdvAt = 'C';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	Tab[5][5] = "rP ";

	//inimigos
	Tab[4][4] = "CC "; // Q 
	Tab[4][5] = "CC "; // W 
	Tab[4][6] = "CC "; // E 
	Tab[5][4] = "CC "; // A 
	Tab[5][6] = "CC "; // D 
	Tab[6][4] = "CC "; // Z 
	Tab[6][5] = "CC "; // X 
	Tab[6][6] = "CC "; // C <<------

	//botar outro rei só pra n ficar resetante o game over
	Tab[1][1] = "rC ";

}

void Teste5(){

	//testando peças CPU
	vez = 2;
	JogAt = 'C';
	AdvAt = 'P';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	Tab[5][5] = "rC ";
	Tab[8][8] = "rP "; // só pra n dar gameover de cara
	/*
	for (int c=1; c<=8; c++){ //peões
    	Tab[2][c] = "PC "; // peão CPU
	}
	*/

	//peças player só pra simular
	for (int c=1; c<=8; c++){ //
    	Tab[7][c] = "TP "; // 
		Tab[2][c] = "TP "; //
		Tab[c][2] = "TP "; // 
		Tab[c][7] = "TP "; // 
	}
}

void Teste6(){

	//testando game over
	vez = 1;
	JogAt = 'P';
	AdvAt = 'C';
	vencedor = 0;

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}

	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "RC ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}
	Tab[5][5] = "RC ";
	Tab[5][3] = "rC ";

	Tab[5][7] = "rP ";

}

void LimpaArena(){

	// garantindo arena vazia antes de prencher
	for (int l=1; l<=8; l++){
    	for (int c=1; c<=8; c++){
        	Tab[l][c] = "  ";// aki n pode ser vazio, se não dá erro da comparação de JogAt ou JogAdv na movimentação de algumas peças
  		}
	}
}