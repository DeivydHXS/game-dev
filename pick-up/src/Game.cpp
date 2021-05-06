#include "Game.h"

// Private functions
void Game::initVariables() {
  this->endGame = false;
  this->spawnTimerMax = 10.f;
  this->spawnTimerMax = this->spawnTimerMax;
  this->maxSwagBalls = 10;
  this->points = 0;
}

void Game::initWindow() {
  this->videoMode = sf::VideoMode(800,600);
  this->window = new sf::RenderWindow(this->videoMode, "Pick Up", sf::Style::Close | sf::Style::Titlebar);
  this->window->setFramerateLimit(60);
}

void Game::initFont() {
  if (!this->font.loadFromFile("fonts/Dosis-Light.ttf")) {
    std::cout << "! ERROR::GAME::INITFONTS::COULD NOT LOAD Dosis-Light.ttf" << "\n";
  }
}

void Game::initText() {
  this->guiText.setFont(this->font);
  this->guiText.setFillColor(sf::Color::White);
  this->guiText.setCharacterSize(32);

  this->endGameText.setFont(this->font);
  this->endGameText.setFillColor(sf::Color::Red);
  this->endGameText.setCharacterSize(66);
  this->endGameText.setPosition(sf::Vector2f(50,300));
  this->endGameText.setString("\t\t\tGame Over!!!\nPress ESC to exit the game...");
}


// Constructor and Destructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initFont();
  this->initText();
}

Game::~Game() {
  delete this->window;
}

const bool& Game::getEndGame() const {
  return this->endGame;
}

const bool Game::isRunning() const {
  return this->window->isOpen();
}

void Game::pollEvents() {
  while (this->window->pollEvent(this->ev)) {
    switch (this->ev.type) {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->ev.key.code == sf::Keyboard::Escape)
          this->window->close();
        break;
    }
  }
}

void Game::spawnSwagBalls() {
  if (this->spawnTimer < this->spawnTimerMax)
    this->spawnTimer += 1.f;
  else
    if (this->swagBalls.size() < this->maxSwagBalls) {
      this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

      this->spawnTimer = 0.f;
    }
}

const int Game::randBallType() {
  int type = SwagBallTypes::DEFAULT;

  int randValue = rand() % 100 + 1;
  if (randValue > 60 && randValue <= 80)
    type = SwagBallTypes::DAMAGING;
  else if (randValue > 80 && randValue <= 100)
    type = SwagBallTypes::HEALING;


  return type;
}

void Game::updatePlayer() {
  this->player.update(this->window);

  if (this->player.getHp() <=  0)
    this->endGame = true;
}

void Game::updateCollision() {
  for (size_t i = 0; i < swagBalls.size(); i++) {
    if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())) {
      switch (this->swagBalls[i].getType()) {
        case SwagBallTypes::DEFAULT:
          this->points += 1;
          break;
        case SwagBallTypes::DAMAGING:
          this->player.takeDamage(5);
          break;
        case SwagBallTypes::HEALING:
          this->player.gainHealth(1);
          break;
      }

      this->swagBalls.erase(this->swagBalls.begin() + i);
    }
  }
}

void Game::updateGUI() {
  std::stringstream ss;

  ss << "Points> " << this->points << "\n"
     << "Health> " << this->player.getHp() << "/" << this->player.getHpMax() << "\n";

  this->guiText.setString(ss.str());
}

void Game::update() {
  this->pollEvents();

  if (this->endGame == false) {
    this->spawnSwagBalls();
    this->updatePlayer();
    this->updateCollision();
    this->updateGUI();
  }

}

void Game::renderGUI(sf::RenderTarget* target) {
  target->draw(this->guiText);
}

void Game::render() {
  this->window->clear();

  this->player.render(this->window);

  for (auto i : this->swagBalls) {
    i.render(*this->window);
  }

  this->renderGUI(this->window);

  if (this->endGame == true)
    this->window->draw(this->endGameText);

  this->window->display();
}
