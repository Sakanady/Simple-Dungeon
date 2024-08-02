#include <iostream>

using namespace std;


class Monster;

class Hero{
    friend Monster;
    private:
        string name;
        int health;
        int healthMax;
        int level;
        int exp;
        int maxExp;
        int strength;
        int dungeonLevel;
    public:
        Hero(string name){
            this->name = name;
            this->health = 10;
            this->healthMax = 10;
            this->level = 1;
            this->exp = 0;
            this->maxExp = 15;
            this->strength = 3;
            this->dungeonLevel = 0;
        }
        void display(){
            cout << "Dungeon Level\t: " << this->dungeonLevel << endl;
            cout << "Name\t\t: " << this->name << endl;
            cout << "Level\t\t: " << this->level << endl;
            cout << "Health\t\t: " << this->health << "/" << this->healthMax << endl; 
            cout << "Experience\t: " << this->exp << "/" << this->maxExp << endl;
            cout << "strength\t: " << this->strength << endl;
        }
        void fightDisplay(){
            cout << "Name\t\t: " << this->name << endl;
            cout << "Level\t\t: " << this->level << endl;
            cout << "Health\t\t: " << this->health << "/" << this->healthMax << endl;
        }
        int getExp(){
            return this->exp;
        }
        int getMaxExp(){
            return this->maxExp;
        }
        int getDungeonLevel(){
            return this->dungeonLevel;
        }
        int getHealth(){
            return this->health;
        }
        int getStrength(){
            return this->strength;
        }
        string getName(){
            return this->name;
        }
        void heal(){
            cout << this->name << " Melakukan Heal" << endl;
            this->health += 3;
            if (this->health > this->healthMax){
                this->health = this->healthMax;
            }
        }
        void levelUp(){
            this->level++;
            int newExp = this->exp - this->maxExp;
            this->exp = newExp;
            this->maxExp +=3;
            this->strength++;
            this->healthMax++;
        }
        void nextDungeon(){
            this->dungeonLevel++;
            cout << "Memasuki dungeon level " << this->dungeonLevel << endl;
        }
        void gainExp(const Monster &obj);
        void gotAttack(const Monster &obj);
};

class Monster{
    friend Hero;
    private:
        string name;
        int health;
        int strength;
        int expDrop;
        int level;
        int maxHealth;
    public:
        Monster(string name){
            this->name = name;
            this->level = 1;
            this->strength = 2;
            this->maxHealth = 8;
            this->health = this->maxHealth;
            this->expDrop = 3;
        }
        string getName(){
            return this->name;
        }
        void display(){
            cout << "Monster Name\t: " << this->name << endl;
            cout << "Monster Level\t: " << this->level << endl;
            cout << "Monster Health\t: " << this->health << endl;
        }
        void levelUp(){
            this->maxHealth++;
            this->expDrop+=2;
            this->strength++;
            this->level++;
        }
        void gotAttack(const Hero &obj){
            cout << "Menyerang " << this->name << endl;
            this->health -= obj.strength;
        }
        void respawn(){
            this->health = this->maxHealth;
        }
        int getHealth(){
            return this->health;
        }
        int getStrength(){
            return this->strength;
        }
        int getExpDrop(){
            return this->expDrop;
        }
};

void Hero::gainExp(const Monster &obj){
    this->exp+=obj.expDrop;
}

void Hero::gotAttack(const Monster &obj){
    cout << "Kamu terkena serangan oleh " << obj.name << endl;
    this->health -= obj.strength;
}

void enterDungeon(Hero &hero, Monster &monster);

void heroDisplay(Hero &hero){
    cout << "==============Hero Info==============" << endl;
    hero.display();
    cout << "=====================================" << endl;
}

void fightInfo(Hero &hero, Monster &monster){
    hero.fightDisplay();
    cout << "=====================================" << endl;
    monster.display();
}

void heroMove(Hero &hero, Monster &monster){
    fightInfo(hero, monster);
    string pilih;
    cout << "[1] Attack\n"
    "[2] Heal\n"
    "[3] Info\n";
    cout << "Masukkan pilihan >>";
    cin >> pilih;
    if (pilih == "1"){
        monster.gotAttack(hero);
        cout << "Nyawa " << monster.getName() << " berkurang " << hero.getStrength() << endl;
    }else if (pilih == "2"){
        hero.heal();
        heroMove(hero, monster);
    }else if (pilih == "3"){
        heroDisplay(hero);
        heroMove(hero, monster);
    }else{
        cout << "PILIHAN TIDAK DITEMUKAN" << endl;
        heroMove(hero, monster);
    }    
}

void monsterMove(Hero &hero, Monster &monster){
    hero.gotAttack(monster);
    cout << "Nyawa kamu berkuarang " << monster.getStrength() << endl;
}

void dungeonClear(Hero &hero, Monster &monster){
    string pilih;
    cout << "[1] Dungeon Selanjutnya\n"
    "[2] Heal\n"
    "[3] Info\n"
    "[4] Exit\n";
    cout << "Masukkan pilihan >>";
    cin >> pilih;
    if (pilih == "1"){
        monster.respawn();
        enterDungeon(hero, monster);
    }else if (pilih == "2"){
        hero.heal();
        dungeonClear(hero, monster);
    }else if (pilih == "3"){
        heroDisplay(hero);
        dungeonClear(hero, monster);
    }else if (pilih == "4"){
        cout << "Permainan Selesai" << endl;
    }else{
        cout << "PILIHAN TIDAK DITEMUKAN" << endl;
        dungeonClear(hero, monster);
    }
}

void heroLose(Hero &hero, Monster &monster){
    cout << hero.getName() << " dikalahkan oleh " << monster.getName() << endl; 
    cout << "Silahkan mengulang permainan" << endl;
}

void monsterLose(Hero &hero, Monster &monster){
    cout << monster.getName() << " telah dikalahkan" << endl; 
    if (hero.getExp() >= hero.getMaxExp()){
        hero.levelUp();
        monster.levelUp();
        dungeonClear(hero, monster);
    }else{
        dungeonClear(hero, monster);
    }
}

void figth(Hero &hero, Monster &monster){
    while (hero.getHealth() > 0 and monster.getHealth() > 0){
        heroMove(hero, monster);
        monsterMove(hero, monster);
    }
    if (hero.getHealth() > 0){
        hero.gainExp(monster);
        monsterLose(hero, monster);
    }else{
        heroLose(hero, monster);
    }    
}

void enterDungeon(Hero &hero, Monster &monster){
    hero.nextDungeon();
    cout << "Kamu bertemu dengan " << monster.getName() << endl;
    cout << "Kamu harus melawannya" << endl;
    figth(hero, monster);

}

void dungeonGate (Hero &hero, Monster &monster){
    string pilih;
    cout << "Karakter berhasi dibuat" << endl;
    cout << "[1] Masuk Dungeon" << endl;
    cout << "[2] Exit" << endl;
    cout << "Masukkan Pilihan >> ";
    cin >> pilih;
    if (pilih == "1"){
        enterDungeon(hero, monster);
    }else if (pilih == "2"){
        return;
    }else{
        cout << "PILIHAN TIDAK ADA" << endl;
    }    
}

void authPlayer(){
    string heroName, monsterName;
    cout << "Masukkan nama hero\t: "; cin >> heroName;
    cout << "Masukkan nama monster\t: "; cin >> monsterName;
    Hero hero1 = Hero(heroName);
    Monster monster1 = Monster(monsterName);
    dungeonGate(hero1, monster1);
}

int main(int argc, char const *argv[])
{
    authPlayer();
    return 0;
}
