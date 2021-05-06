#include "Game.h"

// Private functions +
void Game::initWindow() {
  this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Space Game", sf::Style::Close | sf::Style::Titlebar);
  this->window->setFramerateLimit(144);
  this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures() {
  this->textures["BULLET"] = new sf::Texture();
  this->textures["BULLET"]->loadFromFile("textures/bullet.png");
}

void Game::initGUI() {
  if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
    std::cout << "ERROR::GAME::Failed to load font\n";

  this->pointText.setPosition(700.f, 25.f);
  this->pointText.setFont(font);
  this->pointText.setCharacterSize(20);
  this->pointText.setFillColor(sf::Color::White);
  this->pointText.setString("NONE");

  this->gameOverText.setFont(font);
  this->gameOverText.setCharacterSize(60);
  this->gameOverText.setFillColor(sf::Color::Red);
  this->gameOverText.setString("Game Over!!");
  this->gameOverText.setPosition(
    this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
    this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

  this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
  this->playerHpBar.setFillColor(sf::Color::Red);
  this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

  this->playerHpBarBack = this->playerHpBar;
  this->playerHpBarBack.setFillColor(sf::Color(25,25,25,200));
}

void Game::initWorld() {
  if (!this->worldBgTex.loadFromFile("textures/background.jpg"))
    std::cout << "ERROR::GAME::INITWORLD::Could not load texture.\n";
  this->worldBgSpr.setTexture(this->worldBgTex);
}

void Game::initSystems() {
   this->points = 0;
}

void Game::initPlayer() {
  this->player = new Player();
}

void Game::initEnemies() {
  this->spawnTimerMax = 50.f;
  this->spawnTimer = this->spawnTimerMax;
}

// Constructor and Destructor
Game::Game() {
  this->initWindow();
  this->initTextures();
  this->initGUI();
  this->initWorld();
  this->initSystems();
  this->initPlayer();
  this->initEnemies();
}

Game::~Game() {
  delete this->window;
  delete this->player;

  for (auto &texture : this->textures) {
    delete texture.second;
  }

  for (auto *bullet : this->bullets) {
    delete bullet;
  }

  for (auto *enemy : this->enemies) {
    delete enemy;
  }
}

void Game::run() {
  while (this->window->isOpen()) {
    this->updatePollEvents();

    if (this->player->getHp() > 0)
      this->update();

    this->render();
  }
}

void Game::updatePollEvents() {
  sf::Event e;

  while (this->window->pollEvent(e)) {
    if (e.Event::type == sf::Event::Closed) {
      this->window->close();
    }
    if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
      this->window->close();
    }
  }
}

void Game::updateInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    this->player->move(-1.f, 0.f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    this->player->move(1.f, 0.f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    this->player->move(0.f, -1.f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    this->player->move(0.f, 1.f);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
    this->bullets.push_back(
      new Bullet(this->textures["BULLET"],
      this->player->getPos().x + this->player->getBounds().width/2.f, // Bullt position
      this->player->getPos().y,
      0.f, -1.f, 5.f));
  }
}

void Game::updateGUI() {
  std::stringstream ss;

  ss << "Points> " << this->points;

  this->pointText.setString(ss.str());

  float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
  this->playerHpBar.setSize(sf::Vector2f(this->playerHpBarBack.getSize().x * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld() {

}

void Game::updateCollision() {

  // Left world collision
  if (this->player->getBounds().left < 0.f) {
    this->player->setPosition(0.f, this->player->getBounds().top);
  }

  // Right world collision
  else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
    this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
  }

  // Top world collision
  if (this->player->getBounds().top < 0.f) {
    this->player->setPosition(this->player->getBounds().left, 0.f);
  }

  // Down world collision
  else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
    this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
  }
}

void Game::updateBullets() {
  unsigned counter = 0;
  for (auto *bullet : this->bullets) {

    bullet->update();

    if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
      delete this->bullets.at(counter);
      this->bullets.erase(this->bullets.begin() + counter);
    }

    ++counter;
  }
}

void Game::updateEnemies() {
  this->spawnTimer += 0.5f;
  if (this->spawnTimer >= this->spawnTimerMax) {
    this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
    this->spawnTimer = 0.f;
  }

  unsigned counter = 0;
  for (auto *enemy : this->enemies) {

    enemy->update();

    // Bullet top screen
    if (enemy->getBounds().top > this->window->getSize().y) {
      delete this->enemies.at(counter);
      this->enemies.erase(this->enemies.begin() + counter);
    }

    // Enemy collision Player
    else if (enemy->getBounds().intersects(this->player->getBounds())) {
      this->player->loseHp(this->enemies.at(counter)->getDamage());

      delete this->enemies.at(counter);
      this->enemies.erase(this->enemies.begin() + counter);
    }

    ++counter;
  }
}

void Game::updateCombat() {
  for (int i = 0; i < this->enemies.size(); ++i) {

    bool enemy_deleted = false;
    for (size_t j = 0; j < bullets.size() && enemy_deleted == false; j++) {
      if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds())) {
        this->points += this->enemies[i]->getPoints();

        delete this->enemies[i];
        this->enemies.erase(this->enemies.begin() + i);

        delete this->bullets[j];
        this->bullets.erase(this->bullets.begin() + j);

        enemy_deleted = true;
      }
    }

  }
}

void Game::update() {
  this->updateInput();
  this->player->update();
  this->updateCollision();
  this->updateBullets();
  this->updateEnemies();
  this->updateCombat();
  this->updateGUI();
  this->updateWorld();
}

void Game::renderGUI() {
  this->window->draw(this->pointText);
  this->window->draw(this->playerHpBarBack);
  this->window->draw(this->playerHpBar);
}

void Game::renderWorld() {
  this->window->draw(this->worldBgSpr);
}

void Game::render() {
  this->window->clear();

  this-> renderWorld();

  this->player->render(*this->window);

  for (auto *bullet : this->bullets) {
    bullet->render(*this->window);
  }

  for (auto *enemy : this->enemies) {
    enemy->render(this->window);
  }

  this->renderGUI();

  if (this->player->getHp() <= 0)
    this->window->draw(this->gameOverText);

  this->window->display();
}
