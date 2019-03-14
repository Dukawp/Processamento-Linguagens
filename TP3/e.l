%option noyywrap yylineno


%%


\;							{return yytext[0];}
\,							{return yytext[0];}
\:							{return yytext[0];}
@Emigrante\{		 		{return ABRE;}
@Evento\{					{return ABREE;}
@Obra\{						{return ABREO;}
\}							{return FECHA;}
(?i:Nome)					{return NOME;}
(?i:Data_Nasc)				{return DT;}
(?i:Cidade)					{return CD;}
(?i:Destino) 				{return DST;}
(?i:Data_Em) 				{return DE;}
(?i:Regresso)				{return RG;}
(?i:Data_Rg)				{return DTR;}
(?i:IDEvento)				{return IDE;}
(?i:IDObra)					{return IDO;}
(?i:Descricao)				{return DES;}
(?i:Data)					{return DE;}
\"[^"]*\"					{yytext[strlen(yytext)-1]='\0'; yylval.s = strdup(yytext+1); return STRING;}


.|\n			{;}


%%


int yywarp(){
	return 1;
}