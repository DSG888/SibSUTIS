#include<stdio.h>
#include<conio.h>
#include "myincl.h"

int operand, memory[100],a;
int select = 0;
int asmexit = 0;

void info() {
  clrscr();
  printf("ÚÄÄinfoÄÄÄÄ¿\n");
  printf("³dimcka far³\n");
  printf("³P-01      ³\n");
  printf("³p01s20    ³\n");
  printf("ÀÄÄÄÄÄÄÄÄÄÄÙ\n");
}

int inputmenu() {
  int ch;
  ch = getchar();
  if (ch == 10) ch = getchar();
  return ch;
}

void mainmenu() {
  int ch;
  printf("\n    MENU\n");
  printf("1. load \n");
  printf("2. save \n");
  printf("3. edit\n");
  printf("4. run \n");
  printf("5. memory dump\n");
  printf("6. reset memory dump\n");
  printf("7. save memory dump\n");
  printf("8. exit\n");
  printf("9. about\n\n");
  do {
      ch=inputmenu();
  }
  while ((ch<49) || (ch>57));
  select=ch-48;
}

void edit() {
int instruc;
    clrscr();
    puts("edit");
    a=0;
    do {
      printf("Start address:");
      scanf("%d",&operand);
      if ((operand<0) || (operand>99)){ printf("Invalid address!\n");

      }
      else break;
     } while(1);
     do {
	    printf("%02d : %+05d +>",operand,memory[operand]);
	    scanf("%d",&instruc);
	    if ((instruc < -9999) || (instruc > 9999))  {
		printf("bad command!\n");
	    }
	    else
	    if ((instruc > -9999) || (instruc < 9999))  {
		if (instruc!=-9999){
		    memory[operand] = instruc;
		    operand++;
		}
	    }
	} while ((instruc !=-9999) && (operand <= 99));
	printf("\nEdition completed!\n");
     inputmenu();
}

void memorydump() {
  int i, j;
  clrscr();
  printf("memory dump\n\n");
  for (i=0;i<10;i++) printf("     %d",i);
  printf("\n");
  for (i=0;i<10;i++) {
      printf("%02d ",i*10);
      for (j=0;j<10;j++) {
	   printf("%+05d ",memory[j+i*10]);
      }
      printf("\n");
  }
}

void savememorydump() {
  FILE *fileperemennaja;
  int i, j;
  char filename[11];
  printf("save memory dump to disk\n");
  printf("file:");
  scanf("%s",filename);
  fileperemennaja = fopen(filename, "w+");
  fprintf(fileperemennaja,"memory dump\n");
  for (i=0;i<10;i++) fprintf(fileperemennaja,"     %d",i);
  fprintf(fileperemennaja,"\n");
  for (i=0;i<10;i++) {
      fprintf(fileperemennaja,"%02d ",i*10);
      for (j=0;j<10;j++) {
	  fprintf(fileperemennaja,"%+05d ",memory[j+i*10]);
      }
      fprintf(fileperemennaja,"\n");
  }
  fclose(fileperemennaja);
  printf("memory dump was saved!\n");
}

void runprogr() {
  int accum=0;
  int operand=0;
  int opercod=0;
  int jacheika = 0;
  int temp;
  int halt43 = 0;
  int error=0;
  int a,b,c,d,tempo,i;
  int ok=0;
  clrscr();
  printf("processing..\n");
  do {
      jacheika=memory[operand]%100;
      opercod=memory[operand]/100;
      switch(opercod) {
	  case read     : do{
			  printf("put\n");
			  scanf("%d",&temp);
			  if ((temp<-9999) || (temp>9999)) {
			      printf("error (read)!\n");

			  /*    error=1;*/
			  }
			  else {memory[jacheika]=temp; ok=1;}
			  }while (ok==0);
			  break;
	  case write    : printf("%d\n",memory[jacheika]); break;
	  case load     : accum=memory[jacheika]; break;
	  case store    : memory[jacheika]=accum; break;
	  case add      : accum+=memory[jacheika];
			  if ((accum<-9999) || (accum>9999)) {
			      printf("error! (add)\n");

			/*      halt43=1;*/
			      error=1;
			  }
			  break;
	  case subtract : accum-=memory[jacheika];
			  if ((accum<-9999) || (accum>9999)) {
			      printf("error! (substract)\n");

			      /*halt43=1;*/
			      error=1;
			  }
			  break;
	  case divide   : if (memory[jacheika]==0) {
			      printf("error! (divide)\n");

			      /*halt43=1;*/
			      error=1;
			  }
			  else accum/=memory[jacheika];
			  break;
	  case multiply : accum*=memory[jacheika];
			  if ((accum<-9999) || (accum>9999)) {
			      printf("error! (multiply)\n");

			      /*halt43=1;*/
			      error=1;
			  }
			  break;
	  case branch   : operand=jacheika; break;
	  case branchneg : if (accum<0) operand=jacheika; break;
	  case branchzero : if (accum==0) operand=jacheika; break;
	  case halt     : halt43= 1; break;

	  case rccr	: tempo=(memory[jacheika]);
			  if (accum<0){
			     printf("error! (rccr)\n");
			     halt43 = 1;
			  }
			  else
			  {  for(i=0; i<accum;i++){
				a=tempo/1000;
				b=(tempo%1000)/100;
				c=(tempo%100)/10;
				d=tempo%10;
				tempo=b*1000+c*100+d*10+a;
			  }
			  accum=tempo;
			  }
			  break;
	  default       : printf("error! (default)\n");

			  /*halt43=1;*/
			  error=1;
			  break;
	}

	operand++;
  } while ((error==0) && (operand<100) && (halt43==0));
/*  printf("halt!\n");*/
  if(error==1){
	printf("address=%02d\ncommand=%02d\noperation=%02d",operand-1,opercod,jacheika);
	/*  memorydump();*/
  }
  if (halt43==1)  printf("good!\n"/*"accumulator=%+05d\n",accum*/);
  inputmenu();
}

void loadprogram() {
  FILE *fileproga;
  char filenameto[11];
  printf("\nloading..\n");
  printf("file:");
  scanf("%s",filenameto);
  if ((fileproga = fopen(filenameto, "r")) != NULL) {
      fread(memory,1,100,fileproga);
      fclose(fileproga);
      printf("the load succeeded!\n");
  }
  else {
      printf("error! (load)\n");
  }
}

void saveprogram() {
  FILE *fileproga;
  char filenameto[11];
  printf("\nsaving..\n");
  printf("Output file:");
  scanf("%s",filenameto);
  if ((fileproga = fopen(filenameto, "w")) != NULL) {
      fwrite(memory,1,100,fileproga);
      fclose(fileproga);
      printf("the save succeeded!\n");
  }
  else {
      printf("error! (save)\n");
  }
}

void aboutme() {
int i;
     clrscr();
     printf("\nRCCR\n");
}

int main(void){
     clrscr();
  /*   memset(memory,0,100);*/
     do {
       info();
       mainmenu();
       switch(select)
	{
	  case menu_load     : loadprogram(); inputmenu(); break;
	  case menu_save     : saveprogram(); inputmenu(); break;
	  case menu_editor   : edit(); memorydump(); inputmenu(); break;
	  case menu_run      : runprogr(); break;
	  case menu_dump     : memorydump(); inputmenu(); break;
	  case menu_resetdump: /*memset(memory,0,100);*/ memorydump(); inputmenu(); break;
	  case menu_savedump : savememorydump(); inputmenu(); break;
	  case menu_exit     : asmexit = 1; break;
	  case menu_aboutme  : aboutme(); inputmenu();break;
	}
    } while (asmexit == 0);
    return 0;
}
