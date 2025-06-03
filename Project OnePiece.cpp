#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>

using namespace std;
using namespace sf;

// Глобальные константы и перечисления
enum GameState { MAIN_MENU, LEVEL_SELECTION, BATTLE, LEVEL_TRANSITION, BATTLE_PAUSE, GAME_COMPLETE };
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// ==================== АУДИО МЕНЕДЖЕР ====================
class AudioManager {
private:
    static Music openingMusic;
    static Music battleMusic;
    static Music victoryMusic;
    static SoundBuffer buttonClickBuffer;
    static Sound buttonClickSound;
    static SoundBuffer attackBuffer;
    static Sound attackSound;
    static SoundBuffer hitBuffer;
    static Sound hitSound;
    static bool isInitialized;
    static float musicVolume;

public:
    static void Initialize() {
        if (!isInitialized) {
            if (!openingMusic.openFromFile("C:/Users/Zagre/Desktop/Project op/Music/OpeningMusic.mp3")) {
                cerr << "Failed to load opening music!" << endl;
            }
            openingMusic.setLoop(true);

            if (!battleMusic.openFromFile("C:/Users/Zagre/Desktop/Project op/Music/FightMusic1.mp3")) {
                cerr << "Failed to load battle music!" << endl;
            }
            battleMusic.setLoop(true);

            if (!victoryMusic.openFromFile("C:/Users/Zagre/Desktop/Project op/Music/VictoryMusic.mp3")) {
                cerr << "Failed to load victory music!" << endl;
            }
            victoryMusic.setLoop(false);

            if (!buttonClickBuffer.loadFromFile("C:/Users/Zagre/Desktop/Project op/Music/ChouseLvl.mp3")) {
                cerr << "Failed to load button click sound!" << endl;
            }
            buttonClickSound.setBuffer(buttonClickBuffer);

            if (!attackBuffer.loadFromFile("C:/Users/Zagre/Desktop/Project op/Music/AttackSound.wav")) {
                cerr << "Failed to load attack sound!" << endl;
            }
            attackSound.setBuffer(attackBuffer);

            if (!hitBuffer.loadFromFile("C:/Users/Zagre/Desktop/Project op/Music/HitSound.wav")) {
                cerr << "Failed to load hit sound!" << endl;
            }
            hitSound.setBuffer(hitBuffer);

            musicVolume = 50.0f;
            UpdateVolume();

            isInitialized = true;
        }
    }

    static void PlayOpeningMusic() {
        StopAll();
        openingMusic.play();
    }

    static void PlayBattleMusic() {
        StopAll();
        battleMusic.play();
    }

    static void PlayVictoryMusic() {
        StopAll();
        victoryMusic.play();
    }

    static void PlayButtonClick() {
        buttonClickSound.play();
    }

    static void PlayAttackSound() {
        attackSound.play();
    }

    static void PlayHitSound() {
        hitSound.play();
    }

    static void StopAll() {
        openingMusic.stop();
        battleMusic.stop();
        victoryMusic.stop();
    }

    static void SetVolume(float volume) {
        musicVolume = volume;
        UpdateVolume();
    }

    static float GetVolume() {
        return musicVolume;
    }

    static void UpdateVolume() {
        openingMusic.setVolume(musicVolume);
        battleMusic.setVolume(musicVolume);
        victoryMusic.setVolume(musicVolume);
        buttonClickSound.setVolume(musicVolume);
        attackSound.setVolume(musicVolume);
        hitSound.setVolume(musicVolume);
    }

    static void Cleanup() {
        StopAll();
    }
};

Music AudioManager::openingMusic;
Music AudioManager::battleMusic;
Music AudioManager::victoryMusic;
SoundBuffer AudioManager::buttonClickBuffer;
Sound AudioManager::buttonClickSound;
SoundBuffer AudioManager::attackBuffer;
Sound AudioManager::attackSound;
SoundBuffer AudioManager::hitBuffer;
Sound AudioManager::hitSound;
bool AudioManager::isInitialized = false;
float AudioManager::musicVolume = 50.0f;

// ==================== МЕНЕДЖЕР ШРИФТОВ ====================
class FontManager {
private:
    static Font mainFont;
    static bool isLoaded;

public:
    static bool LoadFont() {
        if (!isLoaded) {
            if (!mainFont.loadFromFile("C:/Users/Zagre/Desktop/Project op/font/one piece font.ttf")) {
                cerr << "Error loading font!" << endl;
                return false;
            }
            isLoaded = true;
        }
        return true;
    }

    static Text CreateText(const string& str, unsigned int size, Color color) {
        Text text(str, mainFont, size);
        text.setFillColor(color);
        return text;
    }

    static const Font& GetFont() { return mainFont; }
};

Font FontManager::mainFont;
bool FontManager::isLoaded = false;

// ==================== МЕНЕДЖЕР ТЕКСТУР ====================
class TextureManager {
private:
    static Texture mainMenuTexture;
    static Texture levelSelectionTexture;
    static Texture battleTexture;
    static Texture levelPanelTexture;
    static Texture lockTexture;
    static Texture finalFrameTexture;
    static Texture luffyTexture;
    static Texture alvidaTexture;
    static Texture morganTexture;
    static Texture buggyTexture;
    static Texture kuroTexture;
    static Texture kriegTexture;
    static Texture arlongTexture;
    static Texture smokerTexture;
    static Texture crocodileTexture;
    static Texture zoroTexture;
    static Texture namiTexture;
    static Texture usoppTexture;
    static Texture sanjiTexture;
    static bool isInitialized;

public:
    static void Initialize() {
        if (!isInitialized) {
            if (!mainMenuTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/Background3.jpg")) {
                cerr << "Failed to load main menu texture!" << endl;
            }

            if (!levelSelectionTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/Background2.jpg")) {
                cerr << "Failed to load level selection texture!" << endl;
            }
            levelSelectionTexture.setRepeated(true);

            if (!battleTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/Background.jpg")) {
                cerr << "Failed to load battle texture!" << endl;
            }
            battleTexture.setRepeated(true);

            if (!levelPanelTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/LevelPanel.jpg")) {
                cerr << "Failed to load level panel texture!" << endl;
            }

            if (!lockTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/Lock.png")) {
                cerr << "Failed to load lock texture!" << endl;
            }

            if (!finalFrameTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/FinalFrame.jpg")) {
                cerr << "Failed to load final frame texture!" << endl;
            }

            if (!luffyTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/LuffyFightingStance.png")) {
                cerr << "Failed to load Luffy texture!" << endl;
            }

            if (!alvidaTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/AlvidaFightingStance.png")) {
                cerr << "Failed to load Alvida texture!" << endl;
            }

            if (!morganTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/MorganFightingStance.png")) {
                cerr << "Failed to load Morgan texture!" << endl;
            }

            if (!buggyTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/BuggyFightingStance.png")) {
                cerr << "Failed to load Buggy texture!" << endl;
            }

            if (!kuroTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/KuroFightingStance.png")) {
                cerr << "Failed to load Kuro texture!" << endl;
            }

            if (!kriegTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/KriegFightingStance.png")) {
                cerr << "Failed to load Krieg texture!" << endl;
            }

            if (!arlongTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/ArlongFightingStance.png")) {
                cerr << "Failed to load Arlong texture!" << endl;
            }

            if (!smokerTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/SmokerFightingStance.png")) {
                cerr << "Failed to load Smoker texture!" << endl;
            }

            if (!crocodileTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/CrocodileFightingStance.png")) {
                cerr << "Failed to load Crocodile texture!" << endl;
            }
            if (!zoroTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/ZoroFightingStance.png")) {
                cerr << "Failed to load Zoro texture!" << endl;
            }
            if (!namiTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/NamiFightingStance.png")) {
                cerr << "Failed to load Nami texture!" << endl;
            }
            if (!usoppTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/UsoppFightingStance.png")) {
                cerr << "Failed to load Usopp texture!" << endl;
            }
            if (!sanjiTexture.loadFromFile("C:/Users/Zagre/Desktop/Project op/images/SanjiFightingStance.png")) {
                cerr << "Failed to load Sanji texture!" << endl;
            }

            isInitialized = true;
        }
    }

    static const Texture& GetMainMenuTexture() { return mainMenuTexture; }
    static const Texture& GetLevelSelectionTexture() { return levelSelectionTexture; }
    static const Texture& GetBattleTexture() { return battleTexture; }
    static const Texture& GetLevelPanelTexture() { return levelPanelTexture; }
    static const Texture& GetLockTexture() { return lockTexture; }
    static const Texture& GetFinalFrameTexture() { return finalFrameTexture; }
    static const Texture& GetLuffyTexture() { return luffyTexture; }
    static const Texture& GetAlvidaTexture() { return alvidaTexture; }
    static const Texture& GetMorganTexture() { return morganTexture; }
    static const Texture& GetBuggyTexture() { return buggyTexture; }
    static const Texture& GetKuroTexture() { return kuroTexture; }
    static const Texture& GetKriegTexture() { return kriegTexture; }
    static const Texture& GetArlongTexture() { return arlongTexture; }
    static const Texture& GetSmokerTexture() { return smokerTexture; }
    static const Texture& GetCrocodileTexture() { return crocodileTexture; }
    static const Texture& GetZoroTexture() { return zoroTexture; }
    static const Texture& GetNamiTexture() { return namiTexture; }
    static const Texture& GetUsoppTexture() { return usoppTexture; }
    static const Texture& GetSanjiTexture() { return sanjiTexture; }
};

Texture TextureManager::mainMenuTexture;
Texture TextureManager::levelSelectionTexture;
Texture TextureManager::battleTexture;
Texture TextureManager::levelPanelTexture;
Texture TextureManager::lockTexture;
Texture TextureManager::finalFrameTexture;
Texture TextureManager::luffyTexture;
Texture TextureManager::alvidaTexture;
Texture TextureManager::morganTexture;
Texture TextureManager::buggyTexture;
Texture TextureManager::kuroTexture;
Texture TextureManager::kriegTexture;
Texture TextureManager::arlongTexture;
Texture TextureManager::smokerTexture;
Texture TextureManager::crocodileTexture;
Texture TextureManager::zoroTexture;
Texture TextureManager::namiTexture;
Texture TextureManager::usoppTexture;
Texture TextureManager::sanjiTexture;
bool TextureManager::isInitialized = false;

// ==================== ОСНОВНОЕ ОКНО ====================
class GameWindow {
private:
    static RenderWindow window;
    static bool isInitialized;

public:
    static void Initialize() {
        if (!isInitialized) {
            window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "One Piece JRPG", Style::Fullscreen);
            window.setFramerateLimit(60);
            isInitialized = true;
        }
    }

    static RenderWindow& GetWindow() { return window; }

    static void Close() {
        window.close();
    }

    static bool IsOpen() { return window.isOpen(); }

    static void Clear() { window.clear(); }

    static void Display() { window.display(); }

    static Vector2f GetMousePosition() {
        return window.mapPixelToCoords(Mouse::getPosition(window));
    }
};

RenderWindow GameWindow::window;
bool GameWindow::isInitialized = false;

// ==================== КЛАСС КНОПКИ ====================
class Button {
protected:
    Sprite sprite;
    Text text;
    Color normalColor;
    Color hoverColor;

public:
    Button(const string& label, const Vector2f& position, unsigned int fontSize,
        Color normal, Color hover) : normalColor(normal), hoverColor(hover) {

        sprite.setTexture(TextureManager::GetLevelPanelTexture());
        sprite.setPosition(position);

        text = FontManager::CreateText(label, fontSize, normal);
        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + sprite.getGlobalBounds().width / 2,
            position.y + sprite.getGlobalBounds().height / 2);
    }

    virtual void Draw() {
        GameWindow::GetWindow().draw(sprite);

        if (IsMouseOver()) {
            text.setFillColor(hoverColor);
        }
        else {
            text.setFillColor(normalColor);
        }

        GameWindow::GetWindow().draw(text);
    }

    bool IsMouseOver() const {
        FloatRect bounds = sprite.getGlobalBounds();
        Vector2f mousePos = GameWindow::GetMousePosition();
        return bounds.contains(mousePos);
    }

    void SetPosition(const Vector2f& position) {
        sprite.setPosition(position);
        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + sprite.getGlobalBounds().width / 2,
            position.y + sprite.getGlobalBounds().height / 2);
    }

    FloatRect GetGlobalBounds() const {
        return sprite.getGlobalBounds();
    }

    void SetScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
        Vector2f pos = sprite.getPosition();
        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(pos.x + sprite.getGlobalBounds().width / 2,
            pos.y + sprite.getGlobalBounds().height / 2);
    }
};

// ==================== КНОПКА УРОВНЯ ====================
class LevelButton : public Button {
private:
    Sprite lockSprite;
    int levelNumber;
    bool isLocked;
    bool isCompleted;

public:
    LevelButton(int level, const Vector2f& position, bool locked = true, bool completed = false)
        : Button("Level " + to_string(level), position, 24,
            completed ? Color::Red : Color::Green,
            completed ? Color(200, 0, 0) : Color(0, 200, 0)),
        levelNumber(level), isLocked(locked), isCompleted(completed) {

        lockSprite.setTexture(TextureManager::GetLockTexture());
        FloatRect bounds = GetGlobalBounds();
        lockSprite.setPosition(position.x + bounds.width / 2 - lockSprite.getGlobalBounds().width / 2,
            position.y + bounds.height / 2 - lockSprite.getGlobalBounds().height / 2);
    }

    void Draw() override {
        Button::Draw();

        if (isLocked) {
            GameWindow::GetWindow().draw(lockSprite);
        }
    }

    bool IsClickable() const {
        return !isLocked && !isCompleted;
    }

    int GetLevelNumber() const { return levelNumber; }
};

// ==================== КНОПКА АТАКИ ====================
class AttackButton : public Button {
private:
    int characterIndex;

public:
    AttackButton(const Vector2f& position, const string& name, Color color, int index)
        : Button(name, position, 24, color, Color(color.r / 2, color.g / 2, color.b / 2)), characterIndex(index) {
        SetScale(0.8f, 0.8f);
    }

    int GetCharacterIndex() const { return characterIndex; }
};

class HealthBar {
private:
    RectangleShape background;
    RectangleShape health;
    float maxHealth;
    float currentHealth;
    Vector2f position;
    bool isEnemy;

public:
    HealthBar(float maxHp, const Vector2f& pos, bool enemy = false)
        : maxHealth(maxHp), currentHealth(maxHp), position(pos), isEnemy(enemy) {
        background.setSize(Vector2f(200, 20));
        background.setFillColor(Color::Black);
        background.setOutlineThickness(2);
        background.setOutlineColor(Color::White);
        background.setPosition(position);

        health.setSize(Vector2f(200, 20));
        health.setFillColor(isEnemy ? Color::Red : Color::Green);
        health.setPosition(position);
    }

    void Update(float newHealth) {
        currentHealth = max(0.0f, min(maxHealth, newHealth));
        health.setSize(Vector2f(200 * (currentHealth / maxHealth), 20));
    }

    void Draw() {
        GameWindow::GetWindow().draw(background);
        GameWindow::GetWindow().draw(health);

        // Отображаем текущее здоровье в виде текста
        string healthText = to_string(static_cast<int>(currentHealth)) + "/" + to_string(static_cast<int>(maxHealth));
        Text text = FontManager::CreateText(healthText, 16, Color::White);
        text.setPosition(position.x + 100 - text.getLocalBounds().width / 2, position.y + 2);
        GameWindow::GetWindow().draw(text);
    }

    void SetPosition(const Vector2f& pos) {
        position = pos;
        background.setPosition(position);
        health.setPosition(position);
    }

    float GetCurrentHealth() const { return currentHealth; }
    float GetMaxHealth() const { return maxHealth; }
    void SetMaxHealth(float newMax) { maxHealth = newMax; }
};

// ==================== ПОЛЗУНОК ГРОМКОСТИ ====================
class VolumeSlider {
private:
    RectangleShape background;
    RectangleShape level;
    Text label;
    float currentVolume;
    Vector2f position;

public:
    VolumeSlider(const Vector2f& pos) : position(pos), currentVolume(AudioManager::GetVolume()) {
        background.setSize(Vector2f(300, 20));
        background.setFillColor(Color(100, 100, 100));
        background.setPosition(position);

        level.setSize(Vector2f(currentVolume * 3, 20));
        level.setFillColor(Color::Green);
        level.setPosition(position);

        label = FontManager::CreateText("Volume", 24, Color::White);
        label.setPosition(position.x, position.y - 40);
    }

    void Draw() {
        GameWindow::GetWindow().draw(background);
        GameWindow::GetWindow().draw(level);
        GameWindow::GetWindow().draw(label);
    }

    void Update(const Vector2f& mousePos) {
        if (IsMouseOver(mousePos)) {
            float relativeX = mousePos.x - position.x;
            currentVolume = max(0.0f, min(100.0f, relativeX / 3.0f));
            AudioManager::SetVolume(currentVolume);
            level.setSize(Vector2f(currentVolume * 3, 20));
        }
    }

    bool IsMouseOver(const Vector2f& mousePos) const {
        FloatRect bounds = background.getGlobalBounds();
        return bounds.contains(mousePos);
    }
};

// ==================== ГЛАВНОЕ МЕНЮ ====================
void ShowMainMenu(GameState& gameState) {
    Sprite background(TextureManager::GetMainMenuTexture());

    // Создаем заголовок
    Text title = FontManager::CreateText("ONE PIECE JRPG", 72, Color::Red);
    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
        titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 100);

    // Создаем текстовые кнопки (без фона)
    Text startButton = FontManager::CreateText("START THE GAME", 48, Color::White);
    FloatRect startBounds = startButton.getLocalBounds();
    startButton.setOrigin(startBounds.left + startBounds.width / 2.0f,
        startBounds.top + startBounds.height / 2.0f);
    startButton.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50);

    Text exitButton = FontManager::CreateText("EXIT", 48, Color::White);
    FloatRect exitBounds = exitButton.getLocalBounds();
    exitButton.setOrigin(exitBounds.left + exitBounds.width / 2.0f,
        exitBounds.top + exitBounds.height / 2.0f);
    exitButton.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 120);

    // Цвета для эффектов наведения
    Color normalColor = Color::White;
    Color hoverColor = Color(255, 215, 0); // Золотой цвет при наведении

    while (GameWindow::IsOpen()) {
        Vector2f mousePos = GameWindow::GetMousePosition();

        // Проверка наведения на кнопки
        bool isStartHovered = startButton.getGlobalBounds().contains(mousePos);
        bool isExitHovered = exitButton.getGlobalBounds().contains(mousePos);

        // Установка цветов в зависимости от наведения
        startButton.setFillColor(isStartHovered ? hoverColor : normalColor);
        exitButton.setFillColor(isExitHovered ? hoverColor : normalColor);

        Event event;
        while (GameWindow::GetWindow().pollEvent(event)) {
            if (event.type == Event::Closed) {
                GameWindow::Close();
                return;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (isStartHovered) {
                    AudioManager::PlayButtonClick();
                    gameState = LEVEL_SELECTION;
                    AudioManager::PlayOpeningMusic();
                    return;
                }

                if (isExitHovered) {
                    AudioManager::PlayButtonClick();
                    GameWindow::Close();
                    return;
                }
            }
        }

        GameWindow::Clear();
        GameWindow::GetWindow().draw(background);
        GameWindow::GetWindow().draw(title);
        GameWindow::GetWindow().draw(startButton);
        GameWindow::GetWindow().draw(exitButton);
        GameWindow::Display();
    }
}

// ==================== ВЫБОР УРОВНЯ ====================
void ShowLevelSelection(GameState& gameState, int& selectedLevel, vector<bool>& completedLevels) {
    // Добавляем фон
    Sprite background(TextureManager::GetLevelSelectionTexture());
    background.setTextureRect(IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    // Проверяем, все ли уровни пройдены
    bool allLevelsCompleted = true;
    for (bool completed : completedLevels) {
        if (!completed) {
            allLevelsCompleted = false;
            break;
        }
    }

    if (allLevelsCompleted) {
        gameState = GAME_COMPLETE;
        return;
    }

    // Настройки расположения кнопок (компактные)
    const float buttonScale = 0.6f;
    const float buttonWidth = TextureManager::GetLevelPanelTexture().getSize().x * buttonScale;
    const float buttonHeight = TextureManager::GetLevelPanelTexture().getSize().y * buttonScale;
    const float buttonSpacingX = 120;
    const float buttonSpacingY = 100;
    const float startX = (WINDOW_WIDTH - (4 * buttonWidth + 3 * buttonSpacingX)) / 2;
    const float startY = 150;

    // Создаем кнопки уровней в 2 ряда (4 в первом, 4 во втором)
    vector<LevelButton> levelButtons;

    // Первый ряд: 4 кнопки
    for (int i = 0; i < 4; ++i) {
        float x = startX + i * (buttonWidth + buttonSpacingX);
        float y = startY;
        bool isLocked = (i > 0) && !completedLevels[i - 1]; // Уровень заблокирован, если предыдущий не пройден
        levelButtons.emplace_back(i + 1, Vector2f(x, y), isLocked, completedLevels[i]);
        levelButtons.back().SetScale(buttonScale, buttonScale);
    }

    // Второй ряд: 4 кнопки
    for (int i = 4; i < 8; ++i) {
        float x = startX + (i - 4) * (buttonWidth + buttonSpacingX);
        float y = startY + buttonHeight + buttonSpacingY;
        bool isLocked = !completedLevels[i - 1]; // Уровень заблокирован, если предыдущий не пройден
        levelButtons.emplace_back(i + 1, Vector2f(x, y), isLocked, completedLevels[i]);
        levelButtons.back().SetScale(buttonScale, buttonScale);
    }

    // Ползунок громкости
    VolumeSlider volumeSlider(Vector2f(WINDOW_WIDTH - 350, 50));
    bool isDraggingVolume = false;

    Text title = FontManager::CreateText("SELECT LEVEL", 48, Color::Black);
    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
        titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(WINDOW_WIDTH / 2.0f, 80);

    Event event;
    while (GameWindow::GetWindow().pollEvent(event)) {
        if (event.type == Event::Closed) {
            GameWindow::Close();
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = GameWindow::GetMousePosition();

            if (volumeSlider.IsMouseOver(mousePos)) {
                isDraggingVolume = true;
                volumeSlider.Update(mousePos);
            }

            for (auto& button : levelButtons) {
                if (button.IsMouseOver() && button.IsClickable()) {
                    AudioManager::PlayButtonClick();
                    selectedLevel = button.GetLevelNumber();
                    gameState = LEVEL_TRANSITION;
                    return;
                }
            }
        }

        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            isDraggingVolume = false;
        }

        if (event.type == Event::MouseMoved && isDraggingVolume) {
            volumeSlider.Update(GameWindow::GetMousePosition());
        }
    }

    GameWindow::Clear();
    GameWindow::GetWindow().draw(background);
    GameWindow::GetWindow().draw(title);

    for (auto& button : levelButtons) {
        button.Draw();
    }

    volumeSlider.Draw();

    GameWindow::Display();
}

// ==================== ПЕРЕХОД НА УРОВЕНЬ ====================
void ShowLevelTransition(GameState& gameState, int selectedLevel) {
    Sprite background(TextureManager::GetBattleTexture());
    background.setTextureRect(IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    Text loadingText = FontManager::CreateText("Loading level " + to_string(selectedLevel) + "...", 36, Color::White);
    FloatRect textBounds = loadingText.getLocalBounds();
    loadingText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    loadingText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    GameWindow::Clear();
    GameWindow::GetWindow().draw(background);
    GameWindow::GetWindow().draw(loadingText);
    GameWindow::Display();

    this_thread::sleep_for(chrono::milliseconds(2000));
    AudioManager::PlayBattleMusic();
    gameState = BATTLE;
}

// ==================== МЕНЮ ПАУЗЫ ====================
void ShowPauseMenu(GameState& gameState) {
    RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(Color(0, 0, 0, 150));

    const float buttonSpacing = 150;
    Button continueButton("Continue", Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - buttonSpacing),
        36, Color::Green, Color(0, 200, 0));
    Button exitButton("Exit", Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + buttonSpacing / 2),
        36, Color::Red, Color(200, 0, 0));

    while (true) {
        Event event;
        while (GameWindow::GetWindow().pollEvent(event)) {
            if (event.type == Event::Closed) {
                GameWindow::Close();
                return;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                return;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (continueButton.IsMouseOver()) {
                    AudioManager::PlayButtonClick();
                    return;
                }

                if (exitButton.IsMouseOver()) {
                    AudioManager::PlayButtonClick();
                    gameState = LEVEL_SELECTION;
                    AudioManager::PlayOpeningMusic();
                    return;
                }
            }
        }

        GameWindow::Clear();
        GameWindow::GetWindow().draw(Sprite(TextureManager::GetBattleTexture()));
        GameWindow::GetWindow().draw(overlay);
        continueButton.Draw();
        exitButton.Draw();
        GameWindow::Display();
    }
}

// ==================== ЭКРАН ПОБЕДЫ ====================
void ShowGameCompleteScreen(GameState& gameState, vector<bool>& completedLevels) {
    AudioManager::PlayVictoryMusic();

    Sprite background(TextureManager::GetFinalFrameTexture());
    Text congratsText = FontManager::CreateText("GENERATIONS", 72, Color::Red);
    Text subtitleText = FontManager::CreateText("You have completed all levels!", 48, Color::Black);
    Text instructionText = FontManager::CreateText("Press any key to return to main menu", 36, Color::Black);

    // Центрирование текста
    FloatRect congratsBounds = congratsText.getLocalBounds();
    congratsText.setOrigin(congratsBounds.left + congratsBounds.width / 2.0f,
        congratsBounds.top + congratsBounds.height / 2.0f);
    congratsText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 100);

    FloatRect subtitleBounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin(subtitleBounds.left + subtitleBounds.width / 2.0f,
        subtitleBounds.top + subtitleBounds.height / 2.0f);
    subtitleText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(instructionBounds.left + instructionBounds.width / 2.0f,
        instructionBounds.top + instructionBounds.height / 2.0f);
    instructionText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 200);

    bool waitingForInput = true;
    while (waitingForInput && GameWindow::IsOpen()) {
        Event event;
        while (GameWindow::GetWindow().pollEvent(event)) {
            if (event.type == Event::Closed) {
                GameWindow::Close();
                return;
            }

            // Реагируем на любую клавишу или клик мыши
            if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed) {
                // Сбрасываем все уровни
                for (size_t i = 0; i < completedLevels.size(); ++i) {
                    completedLevels[i] = false;
                }
                completedLevels[0] = false; // Первый уровень доступен

                AudioManager::PlayOpeningMusic();
                gameState = MAIN_MENU;
                waitingForInput = false;
            }
        }

        GameWindow::Clear();
        GameWindow::GetWindow().draw(background);
        GameWindow::GetWindow().draw(congratsText);
        GameWindow::GetWindow().draw(subtitleText);
        GameWindow::GetWindow().draw(instructionText);
        GameWindow::Display();
    }
}

// ==================== ЭКРАН БИТВЫ ====================
void ShowBattleScreen(int level, GameState& gameState, vector<bool>& completedLevels) {
    bool battleWon = false;
    bool playerTurn = true; // Чей ход: true - игрок, false - враг
    const float characterScale = 2.0f;
    const float buttonScale = 0.4f;
    const float yPos = WINDOW_HEIGHT - 525;
    const float buttonYPos = 100;
    const float healthBarYOffset = 100;

    // Генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> damageDist(5, 15);

    // Персонажи команды
    vector<Sprite> characters;
    vector<HealthBar> healthBars;
    vector<AttackButton> attackButtons;
    vector<Color> colors = { Color::Red, Color::Green, Color(255,165,0), Color(139,69,19), Color::Yellow };
    vector<string> names = { "LUFFY", "ZORO", "NAMI", "USOPP", "SANJI" };
    vector<float> characterDamages = { 15.0f, 12.0f, 8.0f, 7.0f, 10.0f }; // Урон для каждого персонажа

    // Индивидуальные позиции персонажей
    vector<Vector2f> characterPositions = {
        Vector2f(-60, yPos),    // Луффи
        Vector2f(150, yPos),    // Зоро
        Vector2f(450, yPos),    // Нами
        Vector2f(700, yPos),    // Усопп
        Vector2f(950, yPos)    // Санджи
    };

    // Позиции кнопок атаки
    float currentButtonX = WINDOW_WIDTH / 2 - (220 * 2 + 100);

    // Луффи (всегда присутствует)
    Sprite luffy(TextureManager::GetLuffyTexture());
    luffy.setScale(characterScale, characterScale);
    luffy.setPosition(characterPositions[0]);
    characters.push_back(luffy);
    healthBars.emplace_back(100, Vector2f(characterPositions[0].x + 80, characterPositions[0].y - healthBarYOffset));
    attackButtons.emplace_back(Vector2f(currentButtonX, buttonYPos), names[0], colors[0], 0);
    attackButtons.back().SetScale(buttonScale, buttonScale);
    currentButtonX += 220;

    // Добавляем союзников в зависимости от уровня
    if (level >= 3) {
        Sprite zoro(TextureManager::GetZoroTexture());
        zoro.setScale(characterScale, characterScale);
        zoro.setPosition(characterPositions[1]);
        characters.push_back(zoro);
        healthBars.emplace_back(100, Vector2f(characterPositions[1].x + 150, characterPositions[1].y - healthBarYOffset));
        attackButtons.emplace_back(Vector2f(currentButtonX, buttonYPos), names[1], colors[1], 1);
        attackButtons.back().SetScale(buttonScale, buttonScale);
        currentButtonX += 220;
    }
    if (level >= 4) {
        Sprite nami(TextureManager::GetNamiTexture());
        nami.setScale(characterScale, characterScale);
        nami.setPosition(characterPositions[2]);
        characters.push_back(nami);
        healthBars.emplace_back(100, Vector2f(characterPositions[2].x + 80, characterPositions[2].y - healthBarYOffset));
        attackButtons.emplace_back(Vector2f(currentButtonX, buttonYPos), names[2], colors[2], 2);
        attackButtons.back().SetScale(buttonScale, buttonScale);
        currentButtonX += 220;
    }
    if (level >= 5) {
        Sprite usopp(TextureManager::GetUsoppTexture());
        usopp.setScale(characterScale, characterScale);
        usopp.setPosition(characterPositions[3]);
        characters.push_back(usopp);
        healthBars.emplace_back(100, Vector2f(characterPositions[3].x + 80, characterPositions[3].y - healthBarYOffset));
        attackButtons.emplace_back(Vector2f(currentButtonX, buttonYPos), names[3], colors[3], 3);
        attackButtons.back().SetScale(buttonScale, buttonScale);
        currentButtonX += 220;
    }
    if (level >= 6) {
        Sprite sanji(TextureManager::GetSanjiTexture());
        sanji.setScale(characterScale, characterScale);
        sanji.setPosition(characterPositions[4]);
        characters.push_back(sanji);
        healthBars.emplace_back(100, Vector2f(characterPositions[4].x + 80, characterPositions[4].y - healthBarYOffset));
        attackButtons.emplace_back(Vector2f(currentButtonX, buttonYPos), names[4], colors[4], 4);
        attackButtons.back().SetScale(buttonScale, buttonScale);
    }

    // Создаем врага с индивидуальной позицией
    Sprite enemy;
    float enemyXPos = WINDOW_WIDTH - -50;
    float enemyYPos = yPos;

    // Здоровье врага увеличивается с уровнем
    float enemyMaxHealth = 50 + level * 30;
    float enemyHealth = enemyMaxHealth;

    switch (level) {
    case 1:
        enemy.setTexture(TextureManager::GetAlvidaTexture());
        enemyXPos = WINDOW_WIDTH - 150;
        break;
    case 2:
        enemy.setTexture(TextureManager::GetMorganTexture());
        enemyXPos = WINDOW_WIDTH - 120;
        break;
    case 3:
        enemy.setTexture(TextureManager::GetBuggyTexture());
        enemyXPos = WINDOW_WIDTH - 130;
        break;
    case 4:
        enemy.setTexture(TextureManager::GetKuroTexture());
        enemyXPos = WINDOW_WIDTH - 140;
        break;
    case 5:
        enemy.setTexture(TextureManager::GetKriegTexture());
        enemyXPos = WINDOW_WIDTH - 110;
        break;
    case 6:
        enemy.setTexture(TextureManager::GetArlongTexture());
        enemyXPos = WINDOW_WIDTH - 100;
        break;
    case 7:
        enemy.setTexture(TextureManager::GetSmokerTexture());
        enemyXPos = WINDOW_WIDTH - 120;
        break;
    case 8:
        enemy.setTexture(TextureManager::GetCrocodileTexture());
        enemyXPos = WINDOW_WIDTH - 130;
        break;
    }
    enemy.setScale(-characterScale, characterScale);
    enemy.setPosition(enemyXPos, enemyYPos);

    // Шкала здоровья врага
    HealthBar enemyHealthBar(enemyMaxHealth, Vector2f(enemyXPos - 300, enemyYPos - healthBarYOffset), true);

    // Текст с информацией о ходе
    Text turnInfoText = FontManager::CreateText("", 36, Color::White);
    turnInfoText.setPosition(WINDOW_WIDTH / 2 - 150, 50);
    float turnInfoTimer = 0.0f;
    const float turnInfoDisplayTime = 2.0f;

    // Эффект тряски
    float shakeTimer = 0.0f;
    const float shakeDuration = 0.3f;
    Vector2f originalEnemyPosition = enemy.getPosition();
    Vector2f originalCharacterPosition;

    // Основной игровой цикл битвы
    Clock gameClock;
    while (GameWindow::IsOpen() && !battleWon) {
        float deltaTime = gameClock.restart().asSeconds();

        // Обновление таймеров
        if (turnInfoTimer > 0) {
            turnInfoTimer -= deltaTime;
            if (turnInfoTimer <= 0) {
                turnInfoText.setString("");
            }
        }

        if (shakeTimer > 0) {
            shakeTimer -= deltaTime;
            if (shakeTimer <= 0) {
                enemy.setPosition(originalEnemyPosition);
                if (!playerTurn) {
                    for (size_t i = 0; i < characters.size(); ++i) {
                        characters[i].setPosition(characterPositions[i]);
                    }
                }
            }
            else {
                // Тряска врага
                if (playerTurn) {
                    float offsetX = static_cast<float>(rand() % 10 - 5);
                    float offsetY = static_cast<float>(rand() % 10 - 5);
                    enemy.setPosition(originalEnemyPosition.x + offsetX, originalEnemyPosition.y + offsetY);
                }
                // Тряска персонажа
                else {
                    for (size_t i = 0; i < characters.size(); ++i) {
                        float offsetX = static_cast<float>(rand() % 10 - 5);
                        float offsetY = static_cast<float>(rand() % 10 - 5);
                        characters[i].setPosition(characterPositions[i].x + offsetX, characterPositions[i].y + offsetY);
                    }
                }
            }
        }

        Event event;
        while (GameWindow::GetWindow().pollEvent(event)) {
            if (event.type == Event::Closed) {
                GameWindow::Close();
                return;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                ShowPauseMenu(gameState);
                if (gameState != BATTLE) return;
            }

            if (playerTurn && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                for (auto& button : attackButtons) {
                    if (button.IsMouseOver()) {
                        AudioManager::PlayAttackSound();
                        int attackerIndex = button.GetCharacterIndex();
                        float damage = characterDamages[attackerIndex] + damageDist(gen);

                        // Наносим урон врагу
                        enemyHealth = max(0.0f, enemyHealth - damage);
                        enemyHealthBar.Update(enemyHealth);

                        // Эффект тряски врага
                        shakeTimer = shakeDuration;
                        originalEnemyPosition = enemy.getPosition();
                        AudioManager::PlayHitSound();

                        // Устанавливаем текст информации о ходе
                        turnInfoText.setString(names[attackerIndex] + " attacks for " + to_string(static_cast<int>(damage)) + " damage!");
                        turnInfoTimer = turnInfoDisplayTime;

                        // Проверяем, побежден ли враг
                        if (enemyHealth <= 0) {
                            battleWon = true;
                            if (level >= 1 && level <= completedLevels.size()) {
                                completedLevels[level - 1] = true;
                                if (level < completedLevels.size()) {
                                    completedLevels[level] = false;
                                }
                            }
                            gameState = LEVEL_SELECTION;
                            AudioManager::PlayOpeningMusic();
                            return;
                        }

                        // Передаем ход врагу
                        playerTurn = false;
                        break;
                    }
                }
            }
        }

        // Ход врага
        if (!playerTurn && shakeTimer <= 0 && turnInfoTimer <= 0) {
            // Враг атакует случайного персонажа
            uniform_int_distribution<> charDist(0, static_cast<int>(characters.size()) - 1);
            int targetIndex = charDist(gen);
            float damage = 5 + level * 2 + damageDist(gen);

            // Наносим урон персонажу
            float newHealth = healthBars[targetIndex].GetCurrentHealth() - damage;
            healthBars[targetIndex].Update(newHealth);

            // Эффект тряски персонажа
            shakeTimer = shakeDuration;
            originalCharacterPosition = characters[targetIndex].getPosition();
            AudioManager::PlayHitSound();

            // Устанавливаем текст информации о ходе
            turnInfoText.setString("Enemy attacks " + names[targetIndex] + " for " + to_string(static_cast<int>(damage)) + " damage!");
            turnInfoTimer = turnInfoDisplayTime;

            // Проверяем, жив ли персонаж
            if (newHealth <= 0) {
                // Персонаж погиб - убираем его кнопку атаки
                for (auto it = attackButtons.begin(); it != attackButtons.end(); ++it) {
                    if (it->GetCharacterIndex() == targetIndex) {
                        attackButtons.erase(it);
                        break;
                    }
                }
            }

            // Проверяем, проиграл ли игрок (все персонажи мертвы)
            bool allDead = true;
            for (auto& healthBar : healthBars) {
                if (healthBar.GetCurrentHealth() > 0) {
                    allDead = false;
                    break;
                }
            }

            if (allDead) {
                gameState = LEVEL_SELECTION;
                AudioManager::PlayOpeningMusic();
                return;
            }

            // Возвращаем ход игроку
            playerTurn = true;
        }

        // Отрисовка
        GameWindow::Clear();

        // Фон битвы
        Sprite battleBackground(TextureManager::GetBattleTexture());
        battleBackground.setTextureRect(IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
        GameWindow::GetWindow().draw(battleBackground);

        // Информация о битве
        Text battleInfo = FontManager::CreateText("Battle Level " + to_string(level), 48, Color::White);
        battleInfo.setPosition(50, 50);
        GameWindow::GetWindow().draw(battleInfo);

        // Информация о ходе
        GameWindow::GetWindow().draw(turnInfoText);

        // Отрисовка кнопок атаки (только во время хода игрока)
        if (playerTurn && shakeTimer <= 0) {
            for (auto& button : attackButtons) {
                button.Draw();
            }
        }

        // Отрисовка персонажей и их полосок здоровья
        for (size_t i = 0; i < characters.size(); ++i) {
            if (healthBars[i].GetCurrentHealth() > 0) {
                GameWindow::GetWindow().draw(characters[i]);
                healthBars[i].Draw();
            }
        }

        // Отрисовка врага и его полоски здоровья
        GameWindow::GetWindow().draw(enemy);
        enemyHealthBar.Draw();

        // Отображение чей ход
        Text turnText = FontManager::CreateText(playerTurn ? "Your turn" : "Enemy's turn", 36,
            playerTurn ? Color::Green : Color::Red);
        turnText.setPosition(WINDOW_WIDTH - 200, 50);
        GameWindow::GetWindow().draw(turnText);

        GameWindow::Display();
    }
}

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int main() {
    if (!FontManager::LoadFont()) return 1;
    TextureManager::Initialize();
    GameWindow::Initialize();
    AudioManager::Initialize();

    GameState currentState = MAIN_MENU;
    int selectedLevel = 1;
    vector<bool> completedLevels(8, false);
    completedLevels[0] = false; // Первый уровень всегда доступен

    while (GameWindow::IsOpen()) {
        switch (currentState) {
        case MAIN_MENU:
            ShowMainMenu(currentState);
            break;
        case LEVEL_SELECTION:
            ShowLevelSelection(currentState, selectedLevel, completedLevels);
            break;
        case LEVEL_TRANSITION:
            ShowLevelTransition(currentState, selectedLevel);
            break;
        case BATTLE:
            ShowBattleScreen(selectedLevel, currentState, completedLevels);
            break;
        case BATTLE_PAUSE:
            break;
        case GAME_COMPLETE:
            ShowGameCompleteScreen(currentState, completedLevels);
            break;
        }
    }

    AudioManager::Cleanup();
    GameWindow::Close();
    return 0;
}