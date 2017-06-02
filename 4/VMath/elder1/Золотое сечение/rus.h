#include <stdio.h>
#include <string.h>

void Rus(char * array);

void Rus(char * array) {
     int i=0;
     char mass[300];
     strcpy(mass, array);
     while (mass[i] != '\0') {
           if (mass[i] == 'À') mass[i] = 128;
           if (mass[i] == 'Á') mass[i] = 129;
           if (mass[i] == 'Â') mass[i] = 130;
           if (mass[i] == 'Ã') mass[i] = 131;
           if (mass[i] == 'Ä') mass[i] = 132;
           if (mass[i] == 'Å') mass[i] = 133;
           if (mass[i] == '¨') mass[i] = 240;
           if (mass[i] == 'Æ') mass[i] = 134;
           if (mass[i] == 'Ç') mass[i] = 135;
           if (mass[i] == 'È') mass[i] = 136;
           if (mass[i] == 'É') mass[i] = 137;
           if (mass[i] == 'Ê') mass[i] = 138;
           if (mass[i] == 'Ë') mass[i] = 139;
           if (mass[i] == 'Ì') mass[i] = 140;
           if (mass[i] == 'Í') mass[i] = 141;
           if (mass[i] == 'Î') mass[i] = 142;
           if (mass[i] == 'Ï') mass[i] = 143;
           if (mass[i] == 'Ð') mass[i] = 144;
           if (mass[i] == 'Ñ') mass[i] = 145;
           if (mass[i] == 'Ò') mass[i] = 146;
           if (mass[i] == 'Ó') mass[i] = 147;
           if (mass[i] == 'Ô') mass[i] = 148;
           if (mass[i] == 'Õ') mass[i] = 149;
           if (mass[i] == 'Ö') mass[i] = 150;
           if (mass[i] == '×') mass[i] = 151;
           if (mass[i] == 'Ø') mass[i] = 152;
           if (mass[i] == 'Ù') mass[i] = 153;
           if (mass[i] == 'Ú') mass[i] = 154;
           if (mass[i] == 'Û') mass[i] = 155;
           if (mass[i] == 'Ü') mass[i] = 156;
           if (mass[i] == 'Ý') mass[i] = 157;
           if (mass[i] == 'Þ') mass[i] = 158;
           if (mass[i] == 'ß') mass[i] = 159;
           if (mass[i] == 'à') mass[i] = 160;
           if (mass[i] == 'á') mass[i] = 161;
           if (mass[i] == 'â') mass[i] = 162;
           if (mass[i] == 'ã') mass[i] = 163;
           if (mass[i] == 'ä') mass[i] = 164;
           if (mass[i] == 'å') mass[i] = 165;
           if (mass[i] == '¸') mass[i] = 241;
           if (mass[i] == 'æ') mass[i] = 166;
           if (mass[i] == 'ç') mass[i] = 167;
           if (mass[i] == 'è') mass[i] = 168;
           if (mass[i] == 'é') mass[i] = 169;
           if (mass[i] == 'ê') mass[i] = 170;
           if (mass[i] == 'ë') mass[i] = 171;
           if (mass[i] == 'ì') mass[i] = 172;
           if (mass[i] == 'í') mass[i] = 173;
           if (mass[i] == 'î') mass[i] = 174;
           if (mass[i] == 'ï') mass[i] = 175;
           if (mass[i] == 'ð') mass[i] = 224;
           if (mass[i] == 'ñ') mass[i] = 225;
           if (mass[i] == 'ò') mass[i] = 226;
           if (mass[i] == 'ó') mass[i] = 227;
           if (mass[i] == 'ô') mass[i] = 228;
           if (mass[i] == 'õ') mass[i] = 229;
           if (mass[i] == 'ö') mass[i] = 230;
           if (mass[i] == '÷') mass[i] = 231;
           if (mass[i] == 'ø') mass[i] = 232;
           if (mass[i] == 'ù') mass[i] = 233;
           if (mass[i] == 'ú') mass[i] = 234;
           if (mass[i] == 'û') mass[i] = 235;
           if (mass[i] == 'ü') mass[i] = 236;
           if (mass[i] == 'ý') mass[i] = 237;
           if (mass[i] == 'þ') mass[i] = 238;
           if (mass[i] == 'ÿ') mass[i] = 239;
	i++;
     }
	printf("%s", mass);
}
