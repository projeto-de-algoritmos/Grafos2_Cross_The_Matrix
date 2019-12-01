#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;

const int WIDTH=800;
const int HEIGHT=480;

int matrix[10][10];
Font font;

int N = 10, M = 10, K = 2000;

std::string MENORCAMINHO = "Menor caminho: ";
std::string VALORATUAL = "Valor atual: ";
std::string NUMEROTENTATIVAS = "Numero de tentativas: ";
std::string VOCEVENCEU = "Voce venceu!";
std::string MELHORTENTATIVA = "Melhor tentativa: ";

int maximumValue(int n = N, int m = M, int p = K) 
{ 
    bool dp[N][M][K]; 
  
    // Initializing array dp with false value. 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) { 
            for (int k = 0; k < K; k++) 
                dp[i][j][k] = false; 
        } 
    } 
  
    // For each value of dp[i][j][k] 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            for (int k = matrix[i][j]; k <= p; k++) { 
  
                // For first cell and for each value of k 
                if (i == 0 && j == 0) { 
                    if (k == matrix[i][j]) 
                        dp[i][j][k] = true; 
                } 
  
                // For first cell of each row 
                else if (i == 0) { 
                    dp[i][j][k] = (dp[i][j][k] ||  
                        dp[i][j - 1][k - matrix[i][j]]); 
                } 
  
                // For first cell of each column 
                else if (j == 0) { 
                    dp[i][j][k] = (dp[i][j][k] || 
                        dp[i - 1][j][k - matrix[i][j]]); 
                } 
  
                // For rest of the cell 
                else { 
  
                    // Down movement. 
                    dp[i][j][k] = (dp[i][j][k] || 
                        dp[i][j - 1][k - matrix[i][j]]); 
  
                    // Right movement. 
                    dp[i][j][k] = (dp[i][j][k] || 
                        dp[i - 1][j][k - matrix[i][j]]); 
  
                    // Diagonal movement. 
                    //dp[i][j][k] = (dp[i][j][k] || 
                    //    dp[i - 1][j - 1][k - matrix[i][j]]); 
                } 
            } 
        } 
    } 
  
    // Finding maximum k. 
    int ans = 0; 
    int menor = 2000;
    for (ans = p; ans >= 0; ans--) 
        if (dp[n - 1][m - 1][ans]) 
            menor = ans;
            //break;

  
    return menor; 
}

int main(){
    int tentativas = 1;
    int bestRun = 9999999;
	srand(time(NULL));

    font.loadFromFile("Sansation_Regular.ttf");

    int playerX = 0, playerY = 0;
    int solution;
    int playerValue = 0;

    bool isPlaying = true;

    
    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            matrix[i][j] = rand()%90+10;
        }
    }
    matrix[0][0] = 0;
    solution = maximumValue();

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Number of Palindromic Paths in a Matrix");
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

	Sprite sprite;
	RenderTexture t;
	t.create(WIDTH, HEIGHT);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	window.draw(sprite);
	window.display();

    t.display();
    window.draw(sprite);
	window.display();

    const Vector2f v2f(46.0, 46.0);
    RectangleShape r;
    r = RectangleShape(v2f);

    Text textMenorCaminho = Text(MENORCAMINHO+std::to_string(solution), font, 15);
    textMenorCaminho.setFillColor(Color(255, 255, 255));
    textMenorCaminho.setPosition(510, 50);
    t.draw(textMenorCaminho);
    t.display();

    Text textEncontrado = Text(VALORATUAL+std::to_string(playerValue), font, 15);
    textEncontrado.setFillColor(Color(255, 255, 255));
    textEncontrado.setPosition(510, 140);
    t.draw(textEncontrado);
    t.display();

    Text textNumeroTentativas = Text(NUMEROTENTATIVAS+std::to_string(tentativas), font, 15);
    textNumeroTentativas.setFillColor(Color(255, 255, 255));
    textNumeroTentativas.setPosition(510, 230);
    t.draw(textNumeroTentativas);
    t.display();

    Text textMelhorTentativa = Text(MELHORTENTATIVA+"0", font, 15);
    textMelhorTentativa.setFillColor(Color(255, 255, 255));
    textMelhorTentativa.setPosition(510, 320);
    t.draw(textMelhorTentativa);
    t.display();

    Text voceGanhou = Text(VOCEVENCEU, font, 19);
    voceGanhou.setFillColor(Color(255, 255, 255));
    voceGanhou.setPosition(580, 380);

    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            // matrix[i][j]
            int x = i*48, y = j*48;
            r.setPosition(x, y);
            r.setFillColor(Color::White);
            r.setOutlineColor(Color(0, 0, 0));
            r.setOutlineThickness(2);
            std::string value = "";
            value+=std::to_string(matrix[i][j]);
            Text text = Text(value, font, 19);
            text.setPosition(x+10, y+10);
            text.setFillColor(Color(248, 24, 148));
            t.draw(r);
            t.display();
            t.draw(text);
            t.display();
        }
    }

    RectangleShape rRed;
    rRed = RectangleShape(v2f);

    rRed.setFillColor(Color::Transparent);
    rRed.setOutlineColor(Color(0, 173, 238));
    rRed.setOutlineThickness(-4);
    rRed.setPosition(0, 0);
    t.draw(rRed);
    t.display();

    window.draw(sprite);
    window.display();

	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}
            else if(e.type == Event::KeyPressed && isPlaying){
                switch (e.key.code){
                    case Keyboard::Enter :{
                        if(playerX == 0 && playerY == 0){
                            continue;
                        }
                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX = 0;
                        playerY = 0;
                        // TODO: Escrever na tela
                        playerValue = 0;
                        tentativas++;

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
					case Keyboard::Right :{
						if(playerX >= 9){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX++;
                        // TODO: Escrever na tela
                        playerValue+=matrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
                    case Keyboard::Left :{
						if(playerX <= 0){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX--;
                        // TODO: Escrever na tela
                        playerValue+=matrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
                    case Keyboard::Down :{
						if(playerY >= 9){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerY++;
                        // TODO: Escrever na tela
                        playerValue+=matrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();

						break;
					}
                    case Keyboard::Up :{
						if(playerY <= 0){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerY--;
                        // TODO: Escrever na tela
                        playerValue+=matrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();

						break;
					}
					default:{
						continue;
						break;
					}
				}
                if(playerX == 9 && playerY == 9){
                    if(playerValue == solution){
                        t.draw(voceGanhou);
                        t.display();
                        isPlaying = false;
                    }
                    else{
                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";
                        value+=std::to_string(matrix[playerX][playerY]);
                        Text text = Text(value, font, 19);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        bestRun=std::min(bestRun, playerValue);

                        // Pinta proximo de vermelho
                        playerX = 0;
                        playerY = 0;
                        // TODO: Escrever na tela
                        playerValue = 0;
                        tentativas++;

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                    }
                    
                }
            }
		}

        const Vector2f v2fdeleteRect(500.0, 46.0);
        RectangleShape deleteRect;
        deleteRect = RectangleShape(v2fdeleteRect);
        deleteRect.setFillColor(Color::Black);

        deleteRect.setPosition(510, 140);
        t.draw(deleteRect);
        t.display();

        textEncontrado = Text(VALORATUAL+std::to_string(playerValue), font, 15);
        textEncontrado.setFillColor(Color(255, 255, 255));
        textEncontrado.setPosition(510, 140);
        t.draw(textEncontrado);
        t.display();

        deleteRect.setPosition(510, 230);
        t.draw(deleteRect);
        t.display();

        textNumeroTentativas = Text(NUMEROTENTATIVAS+std::to_string(tentativas), font, 15);
        textNumeroTentativas.setFillColor(Color(255, 255, 255));
        textNumeroTentativas.setPosition(510, 230);
        t.draw(textNumeroTentativas);
        t.display();

        deleteRect.setPosition(510, 320);
        t.draw(deleteRect);
        t.display();

        int bestRunValue = (bestRun == 9999999) ? 0 : bestRun;
        textMelhorTentativa = Text(MELHORTENTATIVA+std::to_string(bestRunValue), font, 15);
        textMelhorTentativa.setFillColor(Color(255, 255, 255));
        textMelhorTentativa.setPosition(510, 320);
        t.draw(textMelhorTentativa);
        t.display();

		window.clear();
		window.draw(sprite);
		window.display();
	}

}
