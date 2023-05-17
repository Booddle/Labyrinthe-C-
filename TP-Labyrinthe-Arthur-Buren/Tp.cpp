#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

struct Case
{
    bool N,W,S,E, visite;
};
struct laby
{
    int p; //lignes
    int q; //colones
    Case **tab;
};

struct Cellule
{
    int i ;
    int j ;
};

struct pile
{
    int nbe;
    int taille;
    Cellule *T;
};

laby *cree_laby(int p, int q){
    laby *L;
    L=new laby;
    L->p=p;
    L->q=q;
    Case **T= new Case* [p];
    for (int i = 0; i < p; i++)
    {
        T[i]=new Case [q];
        for (int j = 0; j < q; j++)
        {
            T[i][j].N=0;
            T[i][j].E=0;
            T[i][j].S=0;
            T[i][j].W=0;
        }
        
    }
    L->tab=T;
    return L;
}
void afficher(const laby &a){
    cout<<"affiche Laby"<<endl;
     for (int i = 0; i < a.p; i++){
        for(int j=0;j<a.q;j++){
            cout<<"[i:"<<i<<" j:"<<j<<" ";
            cout<<a.tab[i][j].N;
            cout<<a.tab[i][j].E;
            cout<<a.tab[i][j].S;
            cout<<a.tab[i][j].W;
            cout<<"]";
         } cout<<endl;
}}


 void ouvrir1porte(laby &L,int i,int j,int direction, int &coteasupp){
    if (direction==1 && i!=0 && L.tab[i][j].N==0)
    {
        L.tab[i][j].N=1;
        L.tab[i-1][j].S=1;
        coteasupp=coteasupp-1;
    }else if (direction==2 && j!=L.q-1 && L.tab[i][j].E==0)
    {
        L.tab[i][j].E=1;
        L.tab[i][j+1].W=1;
        coteasupp=coteasupp-1;
    }else if (direction==3 && i!=L.p-1 && L.tab[i][j].S==0)
    {
        L.tab[i][j].S=1;
        L.tab[i+1][j].N=1;
        coteasupp=coteasupp-1;
    }else if (direction==4 && j!=0 && L.tab[i][j].W==0)
    {
        L.tab[i][j].W=1;
        L.tab[i][j-1].E=1;
        coteasupp=coteasupp-1;
    }
}

bool checkopen(laby &L, int posi, int posj, int direction){
    if (direction=1)
    {
        if (posi==0 && L.tab[posi][posj].N==1){
            return false;
        }
        if (posi!=0)
        {
            if(L.tab[posi][posj].N!=L.tab[posi-1][posj].S)
            {
                return false;
            }  
        }        
    }
    if (direction=2)
    {
        if (posj==L.q && L.tab[posi][posj].E==1){
            return false;
        }if (posj!=L.q)
         {
            if(L.tab[posi][posj].E!=L.tab[posi][posj+1].W)
            {
                return false;
            }  
        }
    }
    if (direction=3)
    {
        if (posi==L.p && L.tab[posi][posj].S==1){
            return false;
        }
        if (posi!=L.p)
        {
            if (L.tab[posi][posj].S!=L.tab[posi+1][posj].N)
            {
                return false;
            }
        }  
    }
    if (direction=4)
    {
        if (posj==0 && L.tab[posi][posj].W==1){
            return false;
        }
        if (posj!=0)
        {
            if (L.tab[posi][posj].W!=L.tab[posi][posj-1].E)
            {
                return false;
            }  
        }
    }    
    return true;

}

void fermerfrontiere(laby &L,int &coteasuppr){
    coteasuppr=0;
    for (int i = 0; i < L.p; i++){
        for (int j = 0; j < L.q; j++){
            if(i=0){
                L.tab[i][j].N=0;
                coteasuppr+=1;
            }
            if(i=L.p){
                L.tab[i][j].S=0;
                coteasuppr+=1;
            }
            if(j=0){
                L.tab[i][j].W=0;
                coteasuppr+=1;
            }
            if(j=L.q){
                L.tab[i][j].E=0;
                coteasuppr+=1;
            }
        }        
    }
}

void ouvrirportelaby(laby &L, int pourcent){
    
    int cote=2*(L.p)*(L.q)-(L.p)-(L.q);
    cout<<cote<<" nbr cote"<<endl;
    int coteasupp=(pourcent*cote/100);
    cout<<"ouvre porte : "<<coteasupp<<endl;
    int posi=0,posj=0,direction=1;
    while(coteasupp>0)
    {
        posi=rand()%(L.p);
        posj=rand()%(L.q);
        direction=1+rand()%3;
        cout<<"open :"<<posi<<" "<<posj<<" "<<direction<<endl;
        ouvrir1porte(L,posi,posj,direction,coteasupp);
    }
}

bool coherent(laby &L){ 
    for (int i = 0; i < L.p-1; i++)
    {
        for (int j = 0; j < L.q-1; j++)
        {
            if(checkopen(L,i,j,1)==false){return false;}
            if(checkopen(L,i,j,2)==false){return false;}
            if(checkopen(L,i,j,3)==false){return false;}
            if(checkopen(L,i,j,4)==false){return false;}        
        }
        
    }
    return true;
}

void enregistrer(laby &L,const char *txt){
    ofstream my_cout;
    my_cout.open(txt);
    my_cout<<L.p<<" "<<L.q<<" ";
     for (int i = 0; i < L.p; i++){
        for(int j=0;j<L.q;j++){
            my_cout<<L.tab[i][j].N<<" ";
            my_cout<<L.tab[i][j].E<<" ";
            my_cout<<L.tab[i][j].S<<" ";
            my_cout<<L.tab[i][j].W<<" ";
         }
}}


void lire_Laby(const char  *filename)
{
	ifstream my_cin;
    int p,q;
	my_cin.open(filename);


	my_cin>>p>>q;
	laby *L;
	L=new laby;
    L=cree_laby(p,q);
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<q;j++)
		{
			my_cin>>(*L).tab[i][j].N>>(*L).tab[i][j].E>>(*L).tab[i][j].S>>(*L).tab[i][j].W;
		}
	}
    afficher(*L);
    delete L;
}


bool chemin_valide(laby &L, Cellule *C, int nbC){
    bool valide=1;
    int i=0;
    while (valide==1 && i!=nbC)
    {
        if (C[i+1].i==C[i].i-1 && L.tab[C[i].i][C[i].j].N==0)
       {
        valide=0;
       }
       else if (C[i+1].i==C[i].i+1 && L.tab[C[i].i][C[i].j].S==0)
       {
        valide=0;
       }
       else if (C[i+1].j==C[i].j+1 && L.tab[C[i].i][C[i].j].E==0)
       {
        valide=0;
       } 
       else if (C[i+1].j==C[i].j-1 && L.tab[C[i].i][C[i].j].W==0)
       {
        valide=0;
       }

       i++;      
    }   return valide;
}


//fait en collaboration avec Arthur Buren MI-6
void init(pile & p, int taille)
{
    p.taille=taille;
    p.nbe=0;
    p.T=new Cellule[taille];
}

bool empiler(pile & p, Cellule c)
{
    if((p.nbe)<p.taille)
    {
        p.T[p.nbe]=c;
        (p.nbe)++;
        return true;
    }
    return false;
}

Cellule depiler(pile & p)
{
    if(p.nbe>0)
    {
        p.nbe--;
        return(p.T[p.nbe]);
    }
    else
    {
        cout<<"la pile est vide"<<endl;
        exit(1);
    }
}

bool vide(pile & P)
{
    if(P.nbe==0) return true;
    else return false;
}

bool adjacent_visite (laby &L, Cellule C){ //fonction qui renvoie true si toute les case adjacentes sont visités
    for (int i = 1; i <=4; i++){
        switch (i){
            case 1 : if (C.i > 0) {
                    if (!L.tab[C.i - 1][C.j].visite) {
                        return false;
                    }
                }
                break;
            case 2 : if (C.j < L.q-1){
                    if(!L.tab[C.i][C.j+1].visite){
                        return false;
                    }
                }
                break;
            case 3 : if (C.i < L.p-1) {
                    if (!L.tab[C.i + 1][C.j].visite) {
                        return false;
                    }
                }
                break;
            case 4 : if (C.j > 0){
                    if(!L.tab[C.i][C.j-1].visite){
                        return false;
                    }
                }
            break;

            default:
                return true;
        }
    }
    return true;
}


laby * laby_parfait(int p, int q){  //réalisé en collaboration avec Quentin Garnier MI-I6
    laby *perfect_laby = new laby;
    //on ajouter un attribu a la structure "case" qui est un bouléen "visite"
    perfect_laby = cree_laby(p,q);
    // on initialise le nouvel attribu a false
    for (int i = 0; i < perfect_laby->p; i++) {
        for (int j = 0; j < perfect_laby->q; j++) {
            perfect_laby->tab[i][j].visite = false;
        }
    }
    Cellule *current_cell = new Cellule;
    // on crée la pile de cellules
    pile *pile_cell = new pile;
    init(*pile_cell,p*q);
    int porte = 0 ;
    //on initialise
    current_cell->i = 0; //ligne
    current_cell->j = 0; // collone
    empiler(*pile_cell,*current_cell);
    perfect_laby->tab[current_cell->i][current_cell->j].visite = true;
    while (!vide(*pile_cell)){
        while(!adjacent_visite(*perfect_laby, *current_cell)){
            porte = rand () % 4 +1;

                switch (porte){
                    case 1 ://porte N
                        if (current_cell->i > 0){//on verifie que l'on est pas du coté nord
                            if (!perfect_laby->tab[current_cell->i-1][current_cell->j].visite){
                                perfect_laby->tab[current_cell->i][current_cell->j].N = true;
                                perfect_laby->tab[current_cell->i-1][current_cell->j].S = true;
                                perfect_laby->tab[current_cell->i-1][current_cell->j].visite = true;
                                empiler(*pile_cell, *current_cell);
                                current_cell->i--;
                            }
                        }
                        break;

                    case 2 :// porte E
                        if (current_cell->j < q-1){//on verifie que l'on est pas du coté Est
                            if (!perfect_laby->tab[current_cell->i][current_cell->j+1].visite){
                                perfect_laby->tab[current_cell->i][current_cell->j].E = true;
                                perfect_laby->tab[current_cell->i][current_cell->j+1].W = true;
                                perfect_laby->tab[current_cell->i][current_cell->j+1].visite = true;
                                empiler(*pile_cell, *current_cell);
                                current_cell->j++;
                            }
                        }
                        break;

                    case 3 :
                        if (current_cell->i < p-1){//on verifie que l'on est pas du coté South
                            if (!perfect_laby->tab[current_cell->i+1][current_cell->j].visite){
                                perfect_laby->tab[current_cell->i][current_cell->j].S = true;
                                perfect_laby->tab[current_cell->i+1][current_cell->j].N = true;
                                perfect_laby->tab[current_cell->i+1][current_cell->j].visite = true;
                                empiler(*pile_cell, *current_cell);
                                current_cell->i++;
                            }
                        }
                        break;

                    case 4 :
                        if (current_cell->j > 0){//on verifie que l'on est pas du coté West
                            if (!perfect_laby->tab[current_cell->i][current_cell->j-1].visite){
                                perfect_laby->tab[current_cell->i][current_cell->j].W = true;
                                perfect_laby->tab[current_cell->i][current_cell->j-1].E = true;
                                perfect_laby->tab[current_cell->i][current_cell->j-1].visite = true;
                                empiler(*pile_cell, *current_cell);
                                current_cell->j--;
                            }
                        }
                        break;

                    default:
                        cout << "null" << endl;
                }
            }
            Cellule *c2 = new Cellule;
            *c2= depiler(*pile_cell);
            current_cell->i=c2->i;
            current_cell->j=c2->j;
            delete c2;
    }
    return perfect_laby;
}

int main(){
    srand(time(NULL));
    laby *L;
    L=cree_laby(3,3);
    afficher(*L);
    ouvrirportelaby(*L, 50);
    afficher(*L);
    cout<<coherent(*L)<<endl;
    enregistrer(*L,"toto.txt");
    cout<<"test";
    lire_Laby("toto.txt");
    L=laby_parfait(5,5);
    afficher(*L);
    return 0;
}