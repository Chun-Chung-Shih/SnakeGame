#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

int main() {
	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}


	sf::Vector2i fieldSize(20, 15);

	sf::Texture blockTexture;
	if (!blockTexture.loadFromFile("block.png")) {
		std::cout << "block.png is not found." << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<sf::Vector2i> snake = { {3, 4} };

	sf::Vector2i food(rand() % fieldSize.x, rand() % fieldSize.y);

	sf::Sprite block(blockTexture);
	sf::Sprite block2(blockTexture);

	sf::Vector2f blockSize(
		block.getLocalBounds().width,
		block.getLocalBounds().height);

	sf::VideoMode mode(
		unsigned int(fieldSize.x * blockSize.x),
		unsigned int(fieldSize.y * blockSize.y));

	sf::RenderWindow w(mode, L"貪吃蛇");

	enum class Direction { UP, DOWN, LEFT, RIGHT };
	Direction direction = Direction::RIGHT;

	sf::Clock clock;

	bool isDead = false;
	int count = 0;
	
	//show score in the window
	sf::Text text("Score: ", font, 25);
	sf::Text text2;
	text.setFillColor(sf::Color(0, 255, 0));
	text2.setFillColor(sf::Color(0, 255, 0));
	text.setPosition(15, 2);
	text2.setPosition(15, 2);


	// score
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	std::ostringstream ss;
	ss << "Score: " << count << std::endl;
	sf::Text lblScore;
	lblScore.setCharacterSize(25);
	lblScore.setPosition(10, 10);
	lblScore.setFont(arial);
	lblScore.setString(ss.str());


	while (w.isOpen()) {
			// 使用者互動事件的偵測與處理

			sf::Event evt;
			if (w.pollEvent(evt)) {
				if (evt.type == sf::Event::Closed) {
					w.close();
				}

				if (evt.type == sf::Event::KeyPressed) {
					if (evt.key.code == sf::Keyboard::Up) {
						direction = Direction::UP;
					}
					if (evt.key.code == sf::Keyboard::Down) {
						direction = Direction::DOWN;
					}
					if (evt.key.code == sf::Keyboard::Left) {
						direction = Direction::LEFT;
					}
					if (evt.key.code == sf::Keyboard::Right) {
						direction = Direction::RIGHT;
					}
				}
			}
			
			if (clock.getElapsedTime().asSeconds() >= 0.4f) {
				sf::Vector2i head = snake[0];

				// 物體的移動
				if (direction == Direction::UP) {
					head.y--;
					std::cout << "food(x,y): " << food.x << ", " << food.y << " / head(x,y): " << head.x << ", " << head.y << std::endl;
				}
				if (direction == Direction::DOWN) {
					head.y++;
					std::cout << "food(x,y): " << food.x << ", " << food.y << " / head(x,y): " << head.x << ", " << head.y << std::endl;
				}
				if (direction == Direction::LEFT) {
					head.x--;
					std::cout << "food(x,y): " << food.x << ", " << food.y << " / head(x,y): " << head.x << ", " << head.y << std::endl;
				}
				if (direction == Direction::RIGHT) {
					head.x++;
					std::cout << "food(x,y): " << food.x << ", " << food.y << " / head(x,y): " << head.x << ", " << head.y << std::endl;
				}

				if (head.x < 0 || head.x >= fieldSize.x ||
					head.y < 0 || head.y >= fieldSize.y) {
					isDead = true;
				}

				if (!isDead) {
					// 食物是否被蛇吃到了
					if (food.x == head.x & food.y == head.y) {
						srand((unsigned int)time(0));//加入變數種子
						std::cout << "Eaten" << std::endl;
						food.x = rand() % fieldSize.x;//更新食物的x座標
						food.y = rand() % fieldSize.y;//更新食物的y座標
						sf::Vector2f foodPos(food.x* blockSize.x, food.y* blockSize.y);
						block2.setPosition(foodPos);
						count++;
						std::cout << count << std::endl;
						ss.str("");
						ss << "Score: " << count;
						lblScore.setString(ss.str());
					}
					else {
						snake.pop_back();
					}
					snake.insert(snake.begin(), head);
				}
				clock.restart();
			}
			// 畫面的清除
			if (isDead) {
				w.clear(sf::Color::Red);
			}
			else {
				w.clear();
			}

			// 繪製食物
			if (count == 0) {
				sf::Vector2f foodPos(
					food.x* blockSize.x,
					food.y* blockSize.y);
				block2.setPosition(foodPos);

			}

			w.draw(block2);
			w.draw(lblScore);
			
			// 繪製蛇
			for (const sf::Vector2i& body : snake) {
				sf::Vector2f pos(
					body.x * blockSize.x,
					body.y * blockSize.y);
				block.setPosition(pos);
				w.draw(block);
			}

			w.display();
		}

	return EXIT_SUCCESS;
}