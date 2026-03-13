#include <SFML/Graphics.hpp>
#include <vector>
enum class GameState {
    Playing,
    Paused,
    WinScreen
};
class Paddle {
    public:
        sf::RectangleShape paddle;
        sf::Vector2f velocity;
        float x, y;
        Paddle(float x, float y) {
            paddle.setSize(sf::Vector2f(20.f, 80.f));
            paddle.setFillColor(sf::Color::Green);
            paddle.setPosition(x, y);
            velocity = sf::Vector2f(0.f, 0.f);
        }
};
class LeftPaddle : public Paddle {
    public:
    LeftPaddle(float x, float y) : Paddle(x, y) {}
    void movePaddle(const float& deltaTime) {
        float speed = 300.f * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            paddle.move(0.f, -speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            paddle.move(0.f, speed);
        }
        if (paddle.getPosition().y < 0) {
            paddle.setPosition(paddle.getPosition().x, 0);
        }
        if (paddle.getPosition().y + paddle.getSize().y > 600) {
            paddle.setPosition(paddle.getPosition().x, 600 - paddle.getSize().y);
        }
    }
};
class RightPaddle : public Paddle {
    public:
    RightPaddle(float x, float y) : Paddle(x, y) {}
    void movePaddle(const float& deltaTime) {
        float speed = 300.f * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            paddle.move(0.f, -speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            paddle.move(0.f, speed);
        }
        if (paddle.getPosition().y < 0) {
            paddle.setPosition(paddle.getPosition().x, 0);
        }
        if (paddle.getPosition().y + paddle.getSize().y > 600) {
            paddle.setPosition(paddle.getPosition().x, 600 - paddle.getSize().y);
        }
    }
};
class Ball {
    public:
        sf::RectangleShape ball;
        sf::Vector2f velocity;
        sf::Vector2f spawnPoint = sf::Vector2f(385.f, 285.f);
        Ball() {
            ball.setSize(sf::Vector2f(30.f, 30.f));
            ball.setFillColor(sf::Color::White);
            ball.setPosition(spawnPoint);
            velocity = sf::Vector2f(-200.f, -150.f);
        }
        void ballMovement(const float& deltaTime, Paddle& leftPaddle, Paddle& rightPaddle) {
            ball.move(velocity * deltaTime);
            if (ball.getPosition().y <= 0) {
                velocity.y = std::abs(velocity.y);
            }
            if (ball.getPosition().y + 30 >= 600) {
                velocity.y = -std::abs(velocity.y);
            }
            if (ball.getGlobalBounds().intersects(leftPaddle.paddle.getGlobalBounds())) {
            velocity.x = std::abs(velocity.x);
            }
            if (ball.getGlobalBounds().intersects(rightPaddle.paddle.getGlobalBounds())) {
                velocity.x = -std::abs(velocity.x);
            }
        }
};
class Score {
    public:
        int leftScore;
        int rightScore;
        sf::Font font;
        sf::Text leftScoreText;
        sf::Text rightScoreText;
        Score() {
            leftScore = 0;
            rightScore = 0;
            font.loadFromFile("C:/Users/liqok/OneDrive/Desktop/arial/ARIAL.TTF");
            leftScoreText.setFont(font);
            rightScoreText.setFont(font);
            leftScoreText.setCharacterSize(30);
            rightScoreText.setCharacterSize(30);
            leftScoreText.setFillColor(sf::Color::Red);
            rightScoreText.setFillColor(sf::Color::Red);
            leftScoreText.setPosition(300.f, 20.f);
            rightScoreText.setPosition(500.f, 20.f);
        }
        void updateScore(Ball& ball, Paddle& leftPaddle, Paddle& rightPaddle) {
            if (ball.ball.getPosition().x + 30 <= 0) {
                rightScore++;
                ball.ball.setPosition(ball.spawnPoint);
                ball.velocity = sf::Vector2f(-200.f, -150.f);
                leftPaddle.paddle.setPosition(leftPaddle.paddle.getPosition().x, 250.f);
                rightPaddle.paddle.setPosition(rightPaddle.paddle.getPosition().x, 250.f);
            }
            if (ball.ball.getPosition().x >= 800) {
                leftScore++;
                ball.ball.setPosition(ball.spawnPoint);
                ball.velocity = sf::Vector2f(-200.f, -150.f);
                leftPaddle.paddle.setPosition(leftPaddle.paddle.getPosition().x, 250.f);
                rightPaddle.paddle.setPosition(rightPaddle.paddle.getPosition().x, 250.f);
            }
            leftScoreText.setString(std::to_string(leftScore));
            rightScoreText.setString(std::to_string(rightScore));
        }
        void winScreen(sf::RenderWindow& window) {
            sf::Text winText;
            winText.setFont(font);
            winText.setCharacterSize(50);
            winText.setFillColor(sf::Color::Yellow);
            winText.setPosition(250.f, 350.f);
            if (leftScore >= 5) {
                winText.setString("Player 1 Wins!");
                window.draw(winText);
            }
            if (rightScore >= 5) {
                winText.setString("Player 2 Wins!");
                window.draw(winText);
            }
        }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
    window.setFramerateLimit(60);
    Ball pongball;
    LeftPaddle leftPaddle(50.f, 250.f);
    RightPaddle rightPaddle(750.f, 250.f);
    Score score;
    GameState gameState = GameState::Playing;
    sf::Clock pauseClock;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();
        score.updateScore(pongball, leftPaddle, rightPaddle);
        if (gameState == GameState::Playing) {
            pongball.ballMovement(deltaTime, leftPaddle, rightPaddle);
            leftPaddle.movePaddle(deltaTime);
            rightPaddle.movePaddle(deltaTime);
        }
        if (pongball.ball.getPosition().x + 30 <= 0 || pongball.ball.getPosition().x >= 800) {
            gameState = GameState::Paused;
            pauseClock.restart();
        }
        if (gameState == GameState::Paused) {
            if (pauseClock.getElapsedTime().asSeconds() >= 1.f) {
                gameState = GameState::Playing;
            }
        }
        if (score.leftScore >= 5 || score.rightScore >= 5 && gameState != GameState::WinScreen) {
            gameState = GameState::WinScreen;
            pauseClock.restart();
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        if (gameState == GameState::WinScreen) {
            score.winScreen(window);
            if (pauseClock.getElapsedTime().asSeconds() >= 3.f) {
                score.leftScore = 0;
                score.rightScore = 0;
                gameState = GameState::Playing;
            }
        } else {
            window.draw(pongball.ball);
            window.draw(leftPaddle.paddle);
            window.draw(rightPaddle.paddle);
            window.draw(score.leftScoreText);
            window.draw(score.rightScoreText);
        }
        window.display();
    }

    return 0;
}