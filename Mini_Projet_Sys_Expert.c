#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure des reponses qui pointent sur les questions suivantes
typedef struct Reponse{
	char rps[50];
	struct Question *suivant;
}Reponse;

//structure des questions qui pointent sur les reponses ' les deux forment une arbre
typedef struct Question{
	char qst[50];
	struct Reponse tab[10];
	int p;
}Question;

//chainée les réponses pour former les regles
typedef struct Regle{
	struct Reponse *p;
	struct Regle *next;
}Regle;

//attacher une conclusion finale a chaque regle et l'attacher avec la suivant (liste dans une liste)
typedef struct Base_Regle{
	struct Regle *r;
	struct Base_Regle *next;
	char conclusion[10];
}Base_Regle;

//former une liste avec les réponses de l'utilisateur pour la comparer avec les regles
typedef struct User_Answer{
	char answer[50];
	struct User_Answer *next;
}User_Answer;

//initialiser structure question
Question* Creer_Question(){
    Question *b;
    b=NULL;
    return b;
}

//fonction qui cree une question
Question* Ajouter_Question(char question[]){
    Question *d=Creer_Question();
    d=(Question *)malloc(sizeof(Question));
    strcpy(d->qst,question);
    d->p=0;
    return d;
}

//initialiser structure reponse
Reponse* Creer_Reponse(){
    Reponse *b;
    b=NULL;
    return b;
}

//fonction qui cree une reponse et la pointe vers la question suivante
Reponse* Ajouter_Reponse(Question *question,char reponse[]){
    Reponse *b=Creer_Reponse();
    b=(Reponse *)malloc(sizeof(Reponse));
    b->suivant=question;
    strcpy(b->rps,reponse);
    return b;
}

//fonction pour attacher les reponses a leur question
void Ajouter_reponse_question(Question *head1,Reponse *head2,int pos){
	head1->tab[pos]=*head2;//pos est la position d'insertion suivante
	head1->p++;//variable qui stocke la place suivante ou on insert
}

//initialiser structure regle
Regle* Creer_Regle(){
    Regle *b;
    b=NULL;
    return b;
}

//Algo ajouter a la fin de liste chainne utilise pour chainer les reponses et creer les regles
Regle * Ajouter_Regle(Regle *r,Reponse *t1){
    Regle *b;
    b=(Regle *)malloc(sizeof(Regle));
    b->p=t1;
    b->next=NULL;
	if(r==NULL)
		r=b;
	else{
		Regle *temp=r;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=b;
	}
	return r;
}

//initialiser structure base de regle
Base_Regle* Creer_Base_Regle(){
    Base_Regle *b;
    b=NULL;
    return b;
}

//Algo ajouter a la fin de liste chainne utilise pour chainer les regles et creer une base de regles
Base_Regle * Ajouter_Base_Regle(Base_Regle *br,Regle *r1,char conc[]){
    Base_Regle *b;
    b=(Base_Regle *)malloc(sizeof(Base_Regle));
    b->r=r1;
    strcpy(b->conclusion,conc);
    b->next=NULL;
	if(br==NULL)
		br=b;
	else{
		Base_Regle *temp=br;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=b;
	}
	return br;
}

//initialiser structure user answer
User_Answer* Creer_User_Answer(){
    User_Answer *b;
    b=NULL;
    return b;
}

//Algo ajouter a la fin de liste chainne utilise pour chainer les reponses de l'utilistaeur
User_Answer * Ajouter_User_Answer(User_Answer *r,char p[]){
    User_Answer *b;
    b=(User_Answer *)malloc(sizeof(User_Answer));
    strcpy(b->answer,p);
    b->next=NULL;
	if(r==NULL)
		r=b;
	else{
		User_Answer *temp=r;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=b;
	}
	return r;
}

//fct qui cree l'interface sous la forme question reponse et qui prend les reponses de l'utilistaeur et les passent a la fonction Ajouter_User_Answer
User_Answer * Interface(Question *q){
	int i,flag=0;
	int answer;
	User_Answer *Answers=Creer_User_Answer();
	Question *temp;
	printf("%s \n",q->qst);
	for(i=0;i<q->p;i++){
		printf("%d) %s \n",i+1,q->tab[i].rps);
	}
	do{
	flag=0;
	printf("Entrer une des reponses :");
	scanf("%d",&answer);//on fait un choix avec l'indice de la reponses si l'indice se trouve on prend la reponse et on passe a la qst suivante
	for(i=0;i<q->p;i++){
		if(answer-1 == i) {flag=1;}
	}
	}while(flag!=1);
	Answers=Ajouter_User_Answer(Answers,q->tab[answer-1].rps);
	temp=q->tab[answer-1].suivant;

	while((temp->qst)!=NULL){
		printf("\n%s \n",temp->qst);
		for(i=0;i<temp->p;i++){
			printf("%d) %s \n",i+1,temp->tab[i].rps);
		}
	do{
		flag=0;
		printf("Entrer une des reponses :");
		scanf("%d",&answer);
        for(i=0;i<temp->p;i++){
		    if(answer-1 == i) {flag=1;}
	    }
		}while(flag!=1);
		Answers=Ajouter_User_Answer(Answers,temp->tab[answer-1].rps);
        temp=temp->tab[answer-1].suivant;

	}
	return Answers;
}

//compare les reponses de l'utilistaeur avec les regles dans la base de regle et affiche une conclusion selon les choix
void Moteur_Inference(User_Answer *R,Base_Regle *B){
	User_Answer *temp=R;
	Base_Regle *temp1=B;
	Regle *temp2=Creer_Regle();
	int x;
    while (temp1!= NULL){
		temp2=temp1->r ;
		x=0;
		while (temp!=NULL || temp2!= NULL ){//on pointe sur une regle et la premiere reponse de l'utilisateur et on compare deux a deux jusqua trouver la regle correspondante
			if (strcoll(temp->answer , temp2->p->rps)==0){
				temp=temp->next ;
				temp2=temp2->next ;
			}
			else { x=1;  break ;}
		}
		if (x==0){
			printf(temp1->conclusion );
	    }

		else {
			temp1=temp1->next ;
			temp=R ;

		}
}

}

int main(){
	//creation des questions
	Question *question1=Ajouter_Question("why do you want to learn programming?");
	Question *question2=Ajouter_Question("Do you have any idea ?");
	Question *question3=Ajouter_Question("how do you prefer to learn things ?");
	Question *question4=Ajouter_Question("auto or manuel?");
	Question *question5=Ajouter_Question("wich platforme ?");
	Question *question6=Ajouter_Question("does your web app provid in real time like twitter ?");
    Question *question7=Ajouter_Question("do you want to try something new ?");
    Question *question8=Ajouter_Question("which one is your favorite ?");
    Question *question9=Ajouter_Question("which OS ?");
    Question *question10=Ajouter_Question("what do you think about microsoft ?");
    Question *question11=Ajouter_Question("do you have a startup idea ?");
    Question *question12=Ajouter_Question("which company you want to work for?");
	Question *question13=Ajouter_Question("do you have any knowledge ?");

	/*reponses de la question1*/

	Reponse *reponse1=Ajouter_Reponse(NULL,"pick");
	Reponse *reponse2=Ajouter_Reponse(NULL,"kids");
	Reponse *reponse3=Ajouter_Reponse(question2,"fun");
	Reponse *reponse5=Ajouter_Reponse(question13,"improve My Self");
   	Reponse *reponse6=Ajouter_Reponse(question11,"make Money");



	Ajouter_reponse_question(question1,reponse1,0);
	Ajouter_reponse_question(question1,reponse2,1);
	Ajouter_reponse_question(question1,reponse3,2);
	Ajouter_reponse_question(question1,reponse5,3);
	Ajouter_reponse_question(question1,reponse6,4);


	/*reponses de la question2*/
	Reponse *reponse7=Ajouter_Reponse(question3,"nope");
	Reponse *reponse8=Ajouter_Reponse(question5,"yes");

	Ajouter_reponse_question(question2,reponse7,0);
	Ajouter_reponse_question(question2,reponse8,1);



	/*reponses de la question3*/

	Reponse *reponse9=Ajouter_Reponse(NULL,"easy way");
	Reponse *reponse10=Ajouter_Reponse(NULL,"hard Way");
	Reponse *reponse11=Ajouter_Reponse(question4,"harder Way");

	Ajouter_reponse_question(question3,reponse9,0);
	Ajouter_reponse_question(question3,reponse10,1);
	Ajouter_reponse_question(question3,reponse11,2);
	/*reponses de la question 4 */

	 Reponse *reponse12=Ajouter_Reponse(NULL,"auto");
     Reponse *reponse13=Ajouter_Reponse(NULL,"manuel");



	Ajouter_reponse_question(question4,reponse12,0);
	Ajouter_reponse_question(question4,reponse13,1);


    /*reponses de la questuion 5 */

    Reponse *reponse14=Ajouter_Reponse(question6,"web");
	Reponse *reponse15=Ajouter_Reponse(question10,"entreprise");
	Reponse *reponse16=Ajouter_Reponse(question9,"mobile");
	Reponse *reponse17=Ajouter_Reponse(NULL  ,"gaming");



	Ajouter_reponse_question(question5,reponse14,0);
	Ajouter_reponse_question(question5,reponse15,1);
	Ajouter_reponse_question(question5,reponse16,2);
	Ajouter_reponse_question(question5,reponse17,3);



	/*reponses de la question 6  */
	Reponse *reponse18=Ajouter_Reponse(NULL,"yes");
	Reponse *reponse19=Ajouter_Reponse(NULL,"no");

	Ajouter_reponse_question(question6,reponse18,0);
	Ajouter_reponse_question(question6,reponse19,1);


 /* reponses de la question 7 */
    Reponse *reponse20=Ajouter_Reponse(NULL,"yes");
	Reponse *reponse21=Ajouter_Reponse(question8,"no");

	Ajouter_reponse_question(question7,reponse20,0);
	Ajouter_reponse_question(question7,reponse21,1);




	/*reponses de la question 8*/
	Reponse *reponse22=Ajouter_Reponse(NULL,"lego");
	Reponse *reponse23=Ajouter_Reponse(NULL,"playDo");
	Reponse *reponse24=Ajouter_Reponse(NULL,"oldToy");



	Ajouter_reponse_question(question8,reponse22,0);
	Ajouter_reponse_question(question8,reponse23,1);
	Ajouter_reponse_question(question8,reponse24,2);


         /*reponses de la question 9 ****/

    Reponse *reponse25=Ajouter_Reponse(NULL,"android");
	Reponse *reponse26=Ajouter_Reponse(NULL,"iOS");

	Ajouter_reponse_question(question9,reponse25,0);
	Ajouter_reponse_question(question9,reponse26,1);


	/**reponses de la question10*/
	Reponse *reponse27=Ajouter_Reponse(NULL,"I'm Fan");
	Reponse *reponse28=Ajouter_Reponse(NULL,"Not Bad");
	Reponse *reponse29=Ajouter_Reponse(NULL,"suck");



	Ajouter_reponse_question(question10,reponse27,0);
	Ajouter_reponse_question(question10,reponse28,1);
	Ajouter_reponse_question(question10,reponse29,2);


   /***reponses de la question 11 **/
    Reponse *reponse30=Ajouter_Reponse(question6,"web");
	Reponse *reponse31=Ajouter_Reponse(question10,"entreprise");
	Reponse *reponse32=Ajouter_Reponse(question9,"mobile");
	Reponse *reponse33=Ajouter_Reponse(NULL  ,"gaming");
	Reponse *reponse34=Ajouter_Reponse(question12,"Big Tech");
    Reponse *reponse35=Ajouter_Reponse(NULL  ,"doesn't Matter");


	Ajouter_reponse_question(question11,reponse30,0);
	Ajouter_reponse_question(question11,reponse31,1);
	Ajouter_reponse_question(question11,reponse32,2);
	Ajouter_reponse_question(question11,reponse33,3);
    Ajouter_reponse_question(question11,reponse34,4);
    Ajouter_reponse_question(question11,reponse35,5);


    /**reponses de la question 12 **/

    Reponse *reponse36=Ajouter_Reponse(NULL,"windows");
	Reponse *reponse37=Ajouter_Reponse(NULL,"iOS");
	Reponse *reponse38=Ajouter_Reponse(NULL,"google");
	Reponse *reponse39=Ajouter_Reponse(NULL  ,"facebook");


	Ajouter_reponse_question(question12,reponse36,0);
	Ajouter_reponse_question(question12,reponse37,1);
	Ajouter_reponse_question(question12,reponse38,2);
	Ajouter_reponse_question(question12,reponse39,3);

	/**reponses de la question 13 **/

	Reponse *reponse40=Ajouter_Reponse(NULL,"yes");
	Reponse *reponse41=Ajouter_Reponse(NULL,"no");

	Ajouter_reponse_question(question13,reponse40,0);
	Ajouter_reponse_question(question13,reponse41,1);


    /** creation des regles */
	Regle *regle1=Creer_Regle();
	Regle *regle2=Creer_Regle();
	Regle *regle3=Creer_Regle();
	Regle *regle4=Creer_Regle();
	Regle *regle5=Creer_Regle();
	Regle *regle6=Creer_Regle();
	Regle *regle7=Creer_Regle();
	Regle *regle8=Creer_Regle();
	Regle *regle9=Creer_Regle();
	Regle *regle10=Creer_Regle();
	Regle *regle11=Creer_Regle();
	Regle *regle12=Creer_Regle();
	Regle *regle13=Creer_Regle();
	Regle *regle14=Creer_Regle();
	Regle *regle15=Creer_Regle();
	Regle *regle16=Creer_Regle();
	Regle *regle17=Creer_Regle();
	Regle *regle18=Creer_Regle();
	Regle *regle19=Creer_Regle();
	Regle *regle20=Creer_Regle();
	Regle *regle21=Creer_Regle();
	Regle *regle22=Creer_Regle();
	Regle *regle23=Creer_Regle();
	Regle *regle24=Creer_Regle();
    Regle *regle25=Creer_Regle();
	Regle *regle26=Creer_Regle();
	Regle *regle27=Creer_Regle();
	Regle *regle28=Creer_Regle();
	Regle *regle29=Creer_Regle();
	Regle *regle30=Creer_Regle();
	Regle *regle31=Creer_Regle();
	Regle *regle32=Creer_Regle();
	Regle *regle33=Creer_Regle();
	Regle *regle34=Creer_Regle();
	Regle *regle35=Creer_Regle();
	Regle *regle36=Creer_Regle();

	//chainer les reponses pour former les regles et les insere dans la base de regle
	regle1=Ajouter_Regle(regle1,reponse1);
	Base_Regle *Base1=Creer_Base_Regle();
	Base1=Ajouter_Base_Regle(Base1,regle1,"Python");



	regle2=Ajouter_Regle(regle2,reponse2);
	Base1=Ajouter_Base_Regle(Base1,regle2,"Try scratch then Python");



	regle3=Ajouter_Regle(regle3,reponse3);
	regle3=Ajouter_Regle(regle3,reponse7);
	regle3=Ajouter_Regle(regle3,reponse9);
	Base1=Ajouter_Base_Regle(Base1,regle3,"Try Python");


	regle4=Ajouter_Regle(regle4,reponse3);
	regle4=Ajouter_Regle(regle4,reponse7);
	regle4=Ajouter_Regle(regle4,reponse10);
	Base1=Ajouter_Base_Regle(Base1,regle4,"Try C++");

    regle5=Ajouter_Regle(regle5,reponse3);
	regle5=Ajouter_Regle(regle5,reponse7);
	regle5=Ajouter_Regle(regle5,reponse11);
	regle5=Ajouter_Regle(regle5,reponse12);
	Base1=Ajouter_Base_Regle(Base1,regle5,"Try JAVA");

	regle6=Ajouter_Regle(regle6,reponse3);
	regle6=Ajouter_Regle(regle6,reponse7);
	regle6=Ajouter_Regle(regle6,reponse11);
	regle6=Ajouter_Regle(regle6,reponse13);
	Base1=Ajouter_Base_Regle(Base1,regle6,"Try C");

    regle7=Ajouter_Regle(regle7,reponse3);
	regle7=Ajouter_Regle(regle7,reponse8);
	regle7=Ajouter_Regle(regle7,reponse14);
	regle7=Ajouter_Regle(regle7,reponse18);
	Base1=Ajouter_Base_Regle(Base1,regle7,"Try JavaScript");

    regle8=Ajouter_Regle(regle8,reponse3);
	regle8=Ajouter_Regle(regle8,reponse8);
	regle8=Ajouter_Regle(regle8,reponse14);
	regle8=Ajouter_Regle(regle8,reponse19);
	regle8=Ajouter_Regle(regle8,reponse20);
	Base1=Ajouter_Base_Regle(Base1,regle8,"Try to learn JavaScript");

    regle10=Ajouter_Regle(regle10,reponse3);
	regle10=Ajouter_Regle(regle10,reponse8);
	regle10=Ajouter_Regle(regle10,reponse14);
	regle10=Ajouter_Regle(regle10,reponse19);
	regle10=Ajouter_Regle(regle10,reponse21);
	regle10=Ajouter_Regle(regle10,reponse22);
	Base1=Ajouter_Base_Regle(Base1,regle10,"Pyton");

    regle11=Ajouter_Regle(regle11,reponse3);
	regle11=Ajouter_Regle(regle11,reponse8);
	regle11=Ajouter_Regle(regle11,reponse14);
	regle11=Ajouter_Regle(regle11,reponse19);
	regle11=Ajouter_Regle(regle11,reponse21);
	regle11=Ajouter_Regle(regle11,reponse23);
	Base1=Ajouter_Base_Regle(Base1,regle11,"Ruby");

    regle12=Ajouter_Regle(regle12,reponse3);
	regle12=Ajouter_Regle(regle12,reponse8);
	regle12=Ajouter_Regle(regle12,reponse14);
	regle12=Ajouter_Regle(regle12,reponse19);
	regle12=Ajouter_Regle(regle12,reponse21);
	regle12=Ajouter_Regle(regle12,reponse24);
	Base1=Ajouter_Base_Regle(Base1,regle12,"Php");

    regle13=Ajouter_Regle(regle13,reponse3);
	regle13=Ajouter_Regle(regle13,reponse8);
	regle13=Ajouter_Regle(regle13,reponse16);
	regle13=Ajouter_Regle(regle13,reponse25);
	Base1=Ajouter_Base_Regle(Base1,regle13,"JAVA");

    regle14=Ajouter_Regle(regle14,reponse3);
	regle14=Ajouter_Regle(regle14,reponse8);
	regle14=Ajouter_Regle(regle14,reponse16);
	regle14=Ajouter_Regle(regle14,reponse26);
	Base1=Ajouter_Base_Regle(Base1,regle14,"OBJECTIVE-C");

    regle15=Ajouter_Regle(regle15,reponse3);
	regle15=Ajouter_Regle(regle15,reponse8);
	regle15=Ajouter_Regle(regle15,reponse15);
	regle15=Ajouter_Regle(regle15,reponse27);
	Base1=Ajouter_Base_Regle(Base1,regle15,"C#");

    regle16=Ajouter_Regle(regle16,reponse3);
	regle16=Ajouter_Regle(regle16,reponse8);
	regle16=Ajouter_Regle(regle16,reponse15);
	regle16=Ajouter_Regle(regle16,reponse28);
	Base1=Ajouter_Base_Regle(Base1,regle16,"JAVA");

	regle17=Ajouter_Regle(regle17,reponse3);
	regle17=Ajouter_Regle(regle17,reponse8);
	regle17=Ajouter_Regle(regle17,reponse15);
	regle17=Ajouter_Regle(regle17,reponse29);
	Base1=Ajouter_Base_Regle(Base1,regle17,"JAVA");

	regle18=Ajouter_Regle(regle18,reponse3);
	regle18=Ajouter_Regle(regle18,reponse8);
	regle18=Ajouter_Regle(regle18,reponse17);
	Base1=Ajouter_Base_Regle(Base1,regle18,"C++");

    regle19=Ajouter_Regle(regle19,reponse6);
	regle19=Ajouter_Regle(regle19,reponse35);
	Base1=Ajouter_Base_Regle(Base1,regle19,"Java");

	regle20=Ajouter_Regle(regle20,reponse6);
	regle20=Ajouter_Regle(regle20,reponse36);
	Base1=Ajouter_Base_Regle(Base1,regle20,"C#");

	regle21=Ajouter_Regle(regle21,reponse6);
	regle21=Ajouter_Regle(regle21,reponse34);
	regle21=Ajouter_Regle(regle21,reponse37);
	Base1=Ajouter_Base_Regle(Base1,regle21,"C");

	regle22=Ajouter_Regle(regle22,reponse6);
	regle22=Ajouter_Regle(regle22,reponse34);
	regle22=Ajouter_Regle(regle22,reponse38);
	Base1=Ajouter_Base_Regle(Base1,regle22,"python");

	regle23=Ajouter_Regle(regle23,reponse6);
	regle23=Ajouter_Regle(regle23,reponse34);
	regle23=Ajouter_Regle(regle23,reponse39);
	Base1=Ajouter_Base_Regle(Base1,regle23,"python");

	regle24=Ajouter_Regle(regle24,reponse5);
	regle24=Ajouter_Regle(regle24,reponse34);
	regle24=Ajouter_Regle(regle24,reponse39);
	Base1=Ajouter_Base_Regle(Base1,regle24,"python");

	regle24=Ajouter_Regle(regle24,reponse5);
	regle24=Ajouter_Regle(regle24,reponse7);
	regle24=Ajouter_Regle(regle24,reponse11);
	regle24=Ajouter_Regle(regle24,reponse12);
	Base1=Ajouter_Base_Regle(Base1,regle24,"Try C");

	regle25=Ajouter_Regle(regle25,reponse5);
	regle25=Ajouter_Regle(regle25,reponse7);
	regle25=Ajouter_Regle(regle25,reponse11);
	regle25=Ajouter_Regle(regle25,reponse13);
	Base1=Ajouter_Base_Regle(Base1,regle25,"Try JAVA");

	regle26=Ajouter_Regle(regle26,reponse5);
	regle26=Ajouter_Regle(regle26,reponse40);
	Base1=Ajouter_Base_Regle(Base1,regle26,"Start python");

	regle27=Ajouter_Regle(regle27,reponse5);
	regle27=Ajouter_Regle(regle27,reponse41);
	Base1=Ajouter_Base_Regle(Base1,regle27,"Start C++");

	regle28=Ajouter_Regle(regle28,reponse6);
	regle28=Ajouter_Regle(regle28,reponse30);
	regle28=Ajouter_Regle(regle28,reponse18);
	Base1=Ajouter_Base_Regle(Base1,regle28,"JavaScript");

	regle29=Ajouter_Regle(regle29,reponse6);
	regle29=Ajouter_Regle(regle29,reponse30);
	regle29=Ajouter_Regle(regle29,reponse19);
	Base1=Ajouter_Base_Regle(Base1,regle29,"PhP");

	regle30=Ajouter_Regle(regle30,reponse6);
	regle30=Ajouter_Regle(regle30,reponse33);
	Base1=Ajouter_Base_Regle(Base1,regle30,"C++");

	regle31=Ajouter_Regle(regle31,reponse6);
	regle31=Ajouter_Regle(regle31,reponse31);
	regle31=Ajouter_Regle(regle31,reponse27);
	Base1=Ajouter_Base_Regle(Base1,regle31,"C#");

	regle32=Ajouter_Regle(regle32,reponse6);
	regle32=Ajouter_Regle(regle32,reponse31);
	regle32=Ajouter_Regle(regle32,reponse28);
	Base1=Ajouter_Base_Regle(Base1,regle32,"Java");

	regle33=Ajouter_Regle(regle33,reponse6);
	regle33=Ajouter_Regle(regle33,reponse31);
	regle33=Ajouter_Regle(regle33,reponse29);
	Base1=Ajouter_Base_Regle(Base1,regle33,"Java");

	regle34=Ajouter_Regle(regle34,reponse6);
	regle34=Ajouter_Regle(regle34,reponse32);
	regle34=Ajouter_Regle(regle34,reponse25);
	Base1=Ajouter_Base_Regle(Base1,regle34,"Kotlin");

	regle35=Ajouter_Regle(regle35,reponse6);
	regle35=Ajouter_Regle(regle35,reponse32);
	regle35=Ajouter_Regle(regle35,reponse26);
	Base1=Ajouter_Base_Regle(Base1,regle35,"Objective-C");

	regle36=Ajouter_Regle(regle36,reponse6);
	regle36=Ajouter_Regle(regle36,reponse34);
	regle36=Ajouter_Regle(regle36,reponse36);
	Base1=Ajouter_Base_Regle(Base1,regle36,"C#");

	//creation de chaine des reponses du user
    User_Answer *User_reponses=Creer_User_Answer();

	//appel de la fonction interface pour recuperer les reponses de l'utilisateur
	User_reponses=Interface(question1);

	//appel du moteur pour comparer les reponses user avec les regles dans la base regle et affichere conclusion correspondante
	Moteur_Inference(User_reponses,Base1);
}
