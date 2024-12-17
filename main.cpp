#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include<vector>
#include<math.h>
#include<cstdlib>

using namespace sf;
using namespace std;

class alien {
public:
    Texture* texture;
    Sprite ali;
   
    alien(Texture* texture, Vector2u pos) {

        this->texture = texture;
        this->ali.setTexture(*texture);
        this->ali.setScale(0.5f, 0.5f);

        this->ali.setPosition(pos.x - this->ali.getGlobalBounds().width , rand()% (int)(pos.y - this->ali.getGlobalBounds().height));

    }
    ~alien() {

    }

};

class bullet {
public:
    Texture* texture;
    Sprite bull;
    bullet(Texture* texture, Vector2f pos) {

       
        this->texture = texture;
        this->bull.setTexture(*texture);
        this->bull.setScale(0.4f, 0.4f);

        this->bull.setPosition(pos);

    }
    ~bullet() {

    }

};
class shiping {
public:
    //ship
    Texture *texture;
    Sprite shiper;
   
    int HP ;
    int HPmax = 10;
    vector<bullet>bull;
    vector<alien>ali;

    shiping(Texture *texture) {
        
        this->HP = this->HPmax;
        this->texture = texture;
        this->shiper.setTexture(*texture);
        this->shiper.setScale(0.8f, 0.8f);
      

     
    }

};

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Ship Shoot Scoopa");
  
    window.setFramerateLimit(60);
    

    Texture shiptex;
    shiptex.loadFromFile("Texture/sss.png");

 
    

    //ali
    Texture alitex;
    alitex.loadFromFile("Texture/ali.png");

    Texture mstex;
    mstex.loadFromFile("Texture/ms.png");

    Font font;
    font.loadFromFile("Texture/Sho.otf");



    shiping ship(&shiptex);
    vector<alien>ali;
    ali.push_back(alien(&alitex, window.getSize()));

    Text hptext;
    hptext.setFont(font);
    hptext.setCharacterSize(30);
    hptext.setFillColor(Color::White);

    int sc = 0;
    Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(Color::White);
    score.setPosition(545.f, 10.f);


    Text go;
    go.setFont(font);
    go.setCharacterSize(30);
    go.setFillColor(Color::Red);
    go.setPosition(100.f, window.getSize().y/2);

   

    int st = 12;

    int spt = 0; 



        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
            /*   if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                   window.close();
               }

               if (Mouse::isButtonPressed(Mouse::Right)) {
                   window.close();
               }
               */
               //update
              // shape.move(1, 2);

       //user

            if (ship.HP > 0) {
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    ship.shiper.move(-20.f, 0.f);
                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    ship.shiper.move(0.f, -20.f);
                }
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    ship.shiper.move(20.f, 0.f);
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    ship.shiper.move(0.f, 20.f);
                }

            }
            hptext.setPosition(ship.shiper.getPosition().x, ship.shiper.getPosition().y);
            hptext.setString(to_string(ship.HP) + '/' + to_string(ship.HPmax));




            // enemey movement 
            // 

            if (ship.HP > 0) {
            if (spt < 20) {
                spt++;
            }
            else {
                ali.push_back(alien(&alitex, window.getSize()));
                spt = 0;
            }
            
                for (size_t i = 0; i < ali.size(); i++)
                {
                    ali[i].ali.move(-10.f, 0.f);

                    if (ali[i].ali.getPosition().x <= 0 - ali[i].ali.getGlobalBounds().width) {
                        ali.erase(ali.begin() + i);

                        break;
                    }

                    if (ali[i].ali.getGlobalBounds().intersects(ship.shiper.getGlobalBounds())) {
                        ali.erase(ali.begin() + i);
                        if (ship.HP > 0) {
                            ship.HP--;
                        }



                        break;
                    }
                    for (size_t k = 0; k < ship.bull.size(); k++)
                    {
                        if (ali[i].ali.getGlobalBounds().intersects(ship.bull[k].bull.getGlobalBounds())) {
                            ali.erase(ali.begin() + i);
                            ship.bull.erase(ship.bull.begin() + k);
                            sc++;
                            break;
                        }

                    }
                }
            }

            // collosion with window

            if (ship.shiper.getPosition().x <= 0) {
                ship.shiper.setPosition(0.f, ship.shiper.getPosition().y);
            }
            if (ship.shiper.getPosition().y <= 0) {
                ship.shiper.setPosition(ship.shiper.getPosition().x, 0.f);
            }
            if (ship.shiper.getPosition().x >= window.getSize().x - ship.shiper.getGlobalBounds().width) {
                ship.shiper.setPosition(window.getSize().x - ship.shiper.getGlobalBounds().width, ship.shiper.getPosition().y);

            }

            if (ship.shiper.getPosition().y >= window.getSize().y - ship.shiper.getGlobalBounds().height) {
                ship.shiper.setPosition(ship.shiper.getPosition().x, window.getSize().y - ship.shiper.getGlobalBounds().height);

            }


            //bullets


            if (st < 12) {
                st++;
            }


            else if (Keyboard::isKeyPressed(Keyboard::Space) && st >= 12) {
                ship.bull.push_back(bullet(&mstex, Vector2f(ship.shiper.getPosition().x, ship.shiper.getPosition().y + ship.shiper.getGlobalBounds().height / 3.6f)));
                st = 0;
            }
            if (ship.HP > 0) {
                for (size_t i = 0; i < ship.bull.size(); i++)
                {
                    //move
                    ship.bull[i].bull.move(20.f, 0.f);
                    if (ship.bull[i].bull.getPosition().x > window.getSize().x) {
                        ship.bull.erase(ship.bull.begin() + i);
                    }
                }
            }
            //draw and upadet bg color using this clear(color:: - - )
            window.clear();


            window.draw(ship.shiper);

            for (size_t i = 0; i < ali.size(); i++)
            {
                window.draw(ali[i].ali);
            }

            for (size_t i = 0; i < ship.bull.size(); i++)
            {
                window.draw(ship.bull[i].bull);
            }
            //draw eveertyhing here
         //   window.draw(ali);
          //  window.draw(rect);
            score.setString("Score " + to_string(sc));

            go.setString("GAME OVER ! YOUR SCORE IS " + to_string(sc));

        
        

        if (ship.HP <= 0) {
            window.draw(go);
            
        }
        window.draw(score);
        window.draw(hptext); 

        window.display();
    }

    return 0;
}

   