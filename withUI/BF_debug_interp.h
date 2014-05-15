 
#ifndef BF_DEBUG_INTERP_H
#define BF_DEBUG_INTERP_H
//#define DBG 1
#include <string>
#include <stack>
#include <queue>
#include<stdio.h>
#include <iostream>
#include <QThread>
#include <QApplication>
#include <QTextBrowser>
#include <QtCore/QCoreApplication>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>

class BF_debug_interp : public QThread //: Thread
{
    Q_OBJECT
	/**
	 * Kod programu kory chcemu interpretowac
	 * zapisany bez komentarzy
	*/
    QString code;
	
	/**
	 * stos zapisujacy miejsca
	 * wystapien w kodzie nasow otwierajacych
	 * by moc do nich wrocic i wiedziec czy kod jest komilowaly
	*/
    std::stack<int> loop_beg;
	
    /**
     * @brief queue kolejka do odczytu wartosci z konsoli
     */
    std::queue<unsigned char> queue;

	/**
	 * wskaznik na miejsce w pamieci,
	 * w ktorym aktualnie znajduje sie program
	*/
	int mem_ptr;
	
	/**
	 * wskaznik na miejsce w kodzie,
	 * w korym aktualnie znajduje sie program
	*/
	int code_ptr;
	
	/**
	 * ilosc komorek pamieci jakie ma posiadac maszyna
	 * wartosc podawana w konstruktorze
	*/
	int len;

    /**
     * @brief label wyswietla aktualna pozycje w pamieci
     */
    QLabel *label;

    /**
     * @brief tabWidget lista wartosci w komorkach pamieci
     */
    QTabWidget *tabWidget;

	/**
	 * tablica pamieci programu
	*/
    unsigned char* memory;
	
    /**
     * @brief textBrowser output konsoli
     */
    QTextBrowser *textBrowser;

    /**
     * @brief debugging czy uruchomiono mudul debuggowania
     */
    bool debugging;

    /**
     * @brief nextInstr ile instrukcji przeskoczyc
     */
    int nextInstr;

	/**
	 * metoda usuwajaca z kodu komentarze
	 * @param code kod programu
	 * @return kod programu bez komentarzy i bialych znakow
	*/
    QString ExtractCodeFromString(QString code);
	
	/**
	 * metoda sprawdzajaca czy podany program jest poprawny
	 *  skladniowo i mozna go interpretowac
	*/
	bool checkIfBuildable();
	
    /**
     * @brief debug metoda debuggujaca kod
     */
    void debug();

	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '>'
	 * przesuniecie wskaznika pamieci w prawo
	*/
	void shiftRight();
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '<'
	 * przesuniecie wskaznika pamieci w lewo
	*/
	void shiftLeft();
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '+'
	 * inkrementacja aktualnej komorki pamieci
	*/
	void plus();
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '-'
	 * dekrementacja aktualnej komorki pamieci
	*/
	void minus();
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '.'
	 * wypisanie warosci aktualnej komorki jako znak
	*/
	void dot();
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak ','
	 * wczytanie wartosci z konsoli do aktualnej komorki
	*/
    void comma() ;
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak '['
	 * otwarcie petli jesli wartosc w komorce != 0
	*/
	void bracketLeft();
	
	/**
	 * metoda urachamiana gdy w kodzie interpretujemy znak ']'
	 * przejscie do poczatku petli jesli wartosc w komorca != 0
	*/
	void bracketRight();
	
	/**
	 * metoda pobiera nowa instrukcje do interpretowania
	 * @throw string gdy juz nie ma instrukcji do interpretowania
	 * @return znak instrukcji do interpretowania
	*/
    QChar getInstruction() throw (const std::string);
private slots:
    void slot1(QString s);
    void acLabel();
    void acList(int);
public slots:
    void doNextInstruction();

signals:
    void sign(QString s);
    void sigLabel();
    void sigList(int);

	public:
	
	/**
	 * konstruktor
	 * @param s source code
	 * @param i memory length 
     * @param funkcja wyswietlajaca wynik
     * @throw jesli kod nie jest poprawny skladniowo
	 */
    BF_debug_interp(QString s, int i, QTextBrowser *br) throw (const std::string);

    BF_debug_interp(QString s, int i, QTextBrowser *br, QLabel*, QTabWidget*) throw (const std::string);
    /**
	 * metoda interpretujaca kod
	 * dziala w 2 trybach:
	 * -interpretacji wykonuje kod do konca
	 * -debuggowania wykonuje tylko po jednej instrukcji
	 * @param debug czy chcemy uruchomic w trybie debugowania
	*/
	void interprete(bool debug);

    /**
     * metoda dodaje znak wczytaany z konsoli do kolejki z wejsciem
     * @brief addInput
     */
    void addInput(unsigned char);

    void setDebuggeMode(bool);

    void run();

};

#endif // BF_DEBUG_INTERP_H
