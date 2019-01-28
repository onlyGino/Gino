
#include "gtest\gtest.h"

#include "Attivita.h"
#include "Progetto.h"
#include "TODO.h"



/* Test unitari classe Attivita */

TEST(Attivita, costruttori)
{
	char s[1024];
	Attivita a0;
	Date d(31, 12, 2016);
	Attivita a1("Descrizione", d);

	// test costruttore predefinito
	a0.getDescrizione(s);
	ASSERT_STREQ("", s);
	ASSERT_TRUE(a0.getScadenza().getDay() == 1 && a0.getScadenza().getMonth() == 1 && a0.getScadenza().getYear() == 2000);
	ASSERT_EQ(0, a0.getSvolgimento());
	ASSERT_TRUE(a0.getCompletamento().getDay() == 1 && a0.getCompletamento().getMonth() == 1 && a0.getCompletamento().getYear() == 2000);
	// test costrutore con parametri
	a1.getDescrizione(s);
	ASSERT_STREQ("Descrizione", s);
	ASSERT_TRUE(a1.getScadenza().getDay() == 31 && a1.getScadenza().getMonth() == 12 && a1.getScadenza().getYear() == 2016);
	ASSERT_EQ(0, a1.getSvolgimento());
	ASSERT_TRUE(a1.getCompletamento().getDay() == 1 && a1.getCompletamento().getMonth() == 1 && a1.getCompletamento().getYear() == 2000);
}

TEST(Attivita, setEget)
{
	Date d(31, 12, 2016);
	Attivita a;
	
	// test set/get scadenza
	a.setScadenza(d);
	ASSERT_TRUE(a.getScadenza().getDay() == 31 && a.getScadenza().getMonth() == 12 && a.getScadenza().getYear() == 2016);
	// test set/get svolgimento/completamento
	d.setDate(30, 6, 2016);
	a.setSvoglimento(50, d);
	ASSERT_EQ(50, a.getSvolgimento());
	ASSERT_TRUE(a.getCompletamento().getDay() == 1 && a.getCompletamento().getMonth() == 1 && a.getCompletamento().getYear() == 2000);
	d.setDate(31, 8, 2016);
	a.setSvoglimento(100, d);
	ASSERT_EQ(100, a.getSvolgimento());
	ASSERT_TRUE(a.getCompletamento().getDay() == 31 && a.getCompletamento().getMonth() == 8 && a.getCompletamento().getYear() == 2016);
}


/* Test unitari classe Progetto */

TEST(Progetto, costruttore)
{
	char nome_file[1024] = DIRECTORY_PROGETTI;
	char s[1024];
	Attivita elenco[NUMERO_MASSIMO_ATTIVITA_PROGETTO];
	Date d(31, 12, 2016);

	strcat(nome_file, "Progetto");
	remove(nome_file);
	// test costruttore su nuovo progetto
	Progetto p0("Progetto");
	p0.getDenominazione(s);
	ASSERT_STREQ("Progetto", s);
	ASSERT_EQ(0, p0.elencaAttivita(elenco));
	p0.creaAttivita("Descrizione", d);
	// test costruttore su progetto esistente
	Progetto p1("Progetto");
	ASSERT_EQ(1, p0.elencaAttivita(elenco));
	remove(nome_file);
}

TEST(Progetto, gestioneAttivita)
{
	char s[1024];
	Attivita elenco[NUMERO_MASSIMO_ATTIVITA_PROGETTO];
	Date d;

	Progetto p("Progetto");
	ASSERT_EQ(0, p.elencaAttivita(elenco));
	d.setDate(30, 9, 2016);
	// test creazione/elenco attivita'
	ASSERT_TRUE(p.creaAttivita("Prima", d));
	ASSERT_EQ(1, p.elencaAttivita(elenco));
	ASSERT_FALSE(p.creaAttivita("Prima", d));
	ASSERT_EQ(1, p.elencaAttivita(elenco));
	d.setDate(30, 11, 2016);
	ASSERT_TRUE(p.creaAttivita("Seconda", d));
	ASSERT_EQ(2, p.elencaAttivita(elenco));
	d.setDate(31, 1, 2017);
	ASSERT_TRUE(p.creaAttivita("Terza", d));
	ASSERT_EQ(3, p.elencaAttivita(elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STREQ("Prima", s);
	ASSERT_TRUE(elenco[0].getScadenza().getDay() == 30 && elenco[0].getScadenza().getMonth() == 9 && elenco[0].getScadenza().getYear() == 2016);
	elenco[1].getDescrizione(s);
	ASSERT_STREQ("Seconda", s);
	ASSERT_TRUE(elenco[1].getScadenza().getDay() == 30 && elenco[1].getScadenza().getMonth() == 11 && elenco[1].getScadenza().getYear() == 2016);
	elenco[2].getDescrizione(s);
	ASSERT_STREQ("Terza", s);
	ASSERT_TRUE(elenco[2].getScadenza().getDay() == 31 && elenco[2].getScadenza().getMonth() == 1 && elenco[2].getScadenza().getYear() == 2017);
	d.setDate(31, 12, 2016);
	// test aggiornamento attivita
	ASSERT_FALSE(p.aggiornaAttivita("Quarta", d));
	ASSERT_TRUE(p.aggiornaAttivita("Seconda", d));
	ASSERT_EQ(3, p.elencaAttivita(elenco));
	ASSERT_TRUE(elenco[1].getScadenza().getDay() == 31 && elenco[1].getScadenza().getMonth() == 12 && elenco[1].getScadenza().getYear() == 2016);
	d.setDate(31, 8, 2016);
	ASSERT_FALSE(p.aggiornaAttivita("Quarta", 100, d));
	ASSERT_TRUE(p.aggiornaAttivita("Prima", 50, d));
	ASSERT_EQ(3, p.elencaAttivita(elenco));
	ASSERT_EQ(50, elenco[0].getSvolgimento());
	ASSERT_FALSE(elenco[0].getCompletamento().getDay() == 31 && elenco[0].getCompletamento().getMonth() == 8 && elenco[0].getCompletamento().getYear() == 2016);
	d.setDate(31, 10, 2016);
	ASSERT_TRUE(p.aggiornaAttivita("Seconda", 100, d));
	ASSERT_EQ(3, p.elencaAttivita(elenco));
	ASSERT_EQ(100, elenco[1].getSvolgimento());
	ASSERT_TRUE(elenco[1].getCompletamento().getDay() == 31 && elenco[1].getCompletamento().getMonth() == 10 && elenco[1].getCompletamento().getYear() == 2016);
	// test eliminazione attivita'
	ASSERT_FALSE(p.eliminaAttivita("Quarta"));
	ASSERT_TRUE(p.eliminaAttivita("Prima"));
	ASSERT_EQ(2, p.elencaAttivita(elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STRNE("Prima", s);
	ASSERT_STREQ("Seconda", s);
	elenco[1].getDescrizione(s);
	ASSERT_STRNE("Seconda", s);
	ASSERT_STREQ("Terza", s);
}

TEST(Progetto, elenchiAttivita)
{
	char s[1024];
	Attivita elenco[NUMERO_MASSIMO_ATTIVITA_PROGETTO];
	Date d;

	// test elenco attivita'
	Progetto p("Progetto");
	ASSERT_EQ(2, p.elencaAttivita(elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STREQ("Seconda", s);
	ASSERT_TRUE(elenco[0].getScadenza().getDay() == 31 && elenco[0].getScadenza().getMonth() == 12 && elenco[0].getScadenza().getYear() == 2016);
	ASSERT_EQ(100, elenco[0].getSvolgimento());
	ASSERT_TRUE(elenco[0].getCompletamento().getDay() == 31 && elenco[0].getCompletamento().getMonth() == 10 && elenco[0].getCompletamento().getYear() == 2016);
	elenco[1].getDescrizione(s);
	ASSERT_STREQ("Terza", s);
	ASSERT_TRUE(elenco[1].getScadenza().getDay() == 31 && elenco[1].getScadenza().getMonth() == 1 && elenco[1].getScadenza().getYear() == 2017);
	// test elenco attivita' completate
	ASSERT_EQ(1, p.elencaAttivitaCompletate(elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STREQ("Seconda", s);
	ASSERT_EQ(100, elenco[0].getSvolgimento());
	// test elenco attivita' in scadenza
	d.setDate(30, 6, 2017);
	ASSERT_TRUE(p.creaAttivita("Quarta", d));
	d.setDate(31, 3, 2017);
	ASSERT_EQ(1, p.elencaAttivitaInScadenza(d, elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STREQ("Terza", s);
	ASSERT_TRUE(elenco[0].getScadenza().getDay() == 31 && elenco[0].getScadenza().getMonth() == 1 && elenco[0].getScadenza().getYear() == 2017);
	d.setDate(31, 8, 2017);
	ASSERT_EQ(2, p.elencaAttivitaInScadenza(d, elenco));
	elenco[0].getDescrizione(s);
	ASSERT_STREQ("Terza", s);
	ASSERT_TRUE(elenco[0].getScadenza().getDay() == 31 && elenco[0].getScadenza().getMonth() == 1 && elenco[0].getScadenza().getYear() == 2017);
	elenco[1].getDescrizione(s);
	ASSERT_STREQ("Quarta", s);
	ASSERT_TRUE(elenco[1].getScadenza().getDay() == 30 && elenco[1].getScadenza().getMonth() == 6 && elenco[1].getScadenza().getYear() == 2017);
}

TEST(Progetto, esportazioneElenchiAttivita)
{
	char s[1024], *token;
	Attivita elenco[NUMERO_MASSIMO_ATTIVITA_PROGETTO];
	Date d;
	FILE* file;
	Progetto p("Progetto");
	
	// test esportazione elenco attivita'
	ASSERT_TRUE(p.esportaAttivitaSuFile(CSV, "elenco"));
	file = fopen("elenco.csv", "r");
	if (file == NULL)
	  FAIL();
	else
	    {
			if (!feof(file))
			{
				fscanf(file, "%s\n", s);
				token = strtok(s, ",");
				if (token == NULL)
				  FAIL();
				ASSERT_STREQ("Seconda", token);
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(100, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(31, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(10, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(2016, atoi(token));
			}
			else
				FAIL();
			if (!feof(file))
			{
				fscanf(file, "%s\n", s);
				token = strtok(s, ",");
				if (token == NULL)
					FAIL();
				ASSERT_STREQ("Terza", token);
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(0, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(31, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(1, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(2017, atoi(token));
			}
			else
				FAIL();
			if (!feof(file))
			{
				fscanf(file, "%s\n", s);
				token = strtok(s, ",");
				if (token == NULL)
					FAIL();
				ASSERT_STREQ("Quarta", token);
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(0, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(30, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(6, atoi(token));
				token = strtok(NULL, ",");
				if (token == NULL)
					FAIL();
				ASSERT_EQ(2017, atoi(token));
			}
			else
				FAIL();
			if (!feof(file))
			  FAIL();
	    }
	fclose(file);
	
	// test esportazione attivita' completate
	ASSERT_TRUE(p.esportaAttivitaCompletateSuFile(CSV, "elenco"));
	file = fopen("elenco.csv", "r");
	if (file == NULL)
		FAIL();
	else
	{
		if (!feof(file))
		{
			fscanf(file, "%s\n", s);
			token = strtok(s, ",");
			if (token == NULL)
				FAIL();
			ASSERT_STREQ("Seconda", token);
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(100, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(31, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(10, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(2016, atoi(token));
		}
		else
			FAIL();
		if (!feof(file))
			FAIL();
	}
	fclose(file);
    
	// test esportazione attivita' in scadenza
	d.setDate(31, 8, 2017);
	ASSERT_TRUE(p.esportaAttivitaInScadenzaSuFile(d, CSV, "elenco"));
	file = fopen("elenco.csv", "r");
	if (file == NULL)
		FAIL();
	else
	    {
		 if (!feof(file))
		   {
			fscanf(file, "%s\n", s);
			token = strtok(s, ",");
			if (token == NULL)
				FAIL();
			ASSERT_STREQ("Terza", token);
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(0, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(31, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(1, atoi(token));
			token = strtok(NULL, ",");
			if (token == NULL)
				FAIL();
			ASSERT_EQ(2017, atoi(token));
		  }
		else
			FAIL();
		if (!feof(file))
		  {
		   fscanf(file, "%s\n", s);
		   token = strtok(s, ",");
		   if (token == NULL)
			 FAIL();
		   ASSERT_STREQ("Quarta", token);
		   token = strtok(NULL, ",");
		   if (token == NULL)
			 FAIL();
		   ASSERT_EQ(0, atoi(token));
		   token = strtok(NULL, ",");
		   if (token == NULL)
			 FAIL();
		   ASSERT_EQ(30, atoi(token));
		   token = strtok(NULL, ",");
		   if (token == NULL)
			 FAIL();
		   ASSERT_EQ(6, atoi(token));
		   token = strtok(NULL, ",");
		   if (token == NULL)
			 FAIL();
		   ASSERT_EQ(2017, atoi(token));
		  }
		else
			FAIL();
		if (!feof(file))
		  FAIL();
	}
	fclose(file);
}


/* Test unitari classe TODO */

class TestTODO : public testing::Test
{
public:
	char* progetti[16];

	virtual void SetUp(void)
	{
		for (int i = 0; i < 16; i++)
		   progetti[i] = new char[256];
	}

	virtual void TearDown(void)
	{
		for (int i = 0; i < 16; i++)
		   delete[] progetti[i];
	}
};

TEST_F(TestTODO, eliminaProgetto)
{
	int n;

	// test eliminazione progetto
	n = TODO::elencaProgetti(progetti, 16);
	for (int p = 0; p < n; p++)
	{
		ASSERT_TRUE(TODO::eliminaProgetto(progetti[p]));
		ASSERT_FALSE(TODO::eliminaProgetto(progetti[p]));
	}
	ASSERT_EQ(0, TODO::elencaProgetti(progetti, 16));
}

TEST_F(TestTODO, creazioneEelencoProgetti)
{
	Progetto* p;
	char d[256];

	// test creazione progetto
	ASSERT_TRUE(p = TODO::creaProgetto("Progetto1"));
	p->getDenominazione(d);
	ASSERT_STREQ("Progetto1", d);
	delete p;
	ASSERT_FALSE(p = TODO::creaProgetto("Progetto1"));
	ASSERT_TRUE(p = TODO::creaProgetto("Progetto2"));
	p->getDenominazione(d);
	ASSERT_STREQ("Progetto2", d);
	delete p;
	ASSERT_TRUE(p = TODO::creaProgetto("Progetto3"));
	p->getDenominazione(d);
	ASSERT_STREQ("Progetto3", d);
	delete p;

	// test elenco progetti
	ASSERT_EQ(3, TODO::elencaProgetti(progetti, 4));
	ASSERT_STREQ("Progetto1", progetti[0]);
	ASSERT_STREQ("Progetto2", progetti[1]);
	ASSERT_STREQ("Progetto3", progetti[2]);
}

TEST_F(TestTODO, selezioneProgetto)
{
	Progetto* p;
	char d[256];

	// test selezione progetto
	ASSERT_FALSE(p = TODO::selezionaProgetto("Progetto"));
	ASSERT_TRUE(p = TODO::selezionaProgetto("Progetto2"));
	p->getDenominazione(d);
	ASSERT_STREQ("Progetto2", d);
	delete p;
}




int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
