# Chương 2: Tài nguyên của game 

---

## A. TÀI NGUYÊN GAME

#### Các tài nguyên của game được lưu trong folder “assets”, bao gồm:

| `Asset` | Tài Nguyên | Mô Tả 
| - | - | -
| `Audio` | Âm thanh | Chứa những file âm thanh dưới định dạng .mp3
| `Background` | Hình nền | Chứa những lớp hình nền của các ải trong game
| `BlockTile` | Hình khối | Chứa những file hình ảnh của các block tạo thành ải
| `Decoration` | Trang trí | Chứa những file hình ảnh nhằm mục đích trang trí ải
| `Door` | Cửa | Chứa những file hình ảnh của cửa, các trạng thái mở đóng
| `HudElement` | Hiển thị trực quan | Chứa những hình ảnh giao diện luôn hiện trên màn hình chơi
| `IntroLogo` | Chứa những hình ảnh xuất hiện khi mở game (nhà phát hành,…)
| `Menu` | Menu | Chứa những hình nền, nút bấm ở menu chính
| `NakuSheet` | Dải hình nhân vật chính | Chứa những tập hợp các dải hình của người chơi (gồm 2 dải cho 2 hướng trái, phải)
| `NpcSheet` | Dải hình Npc | Chứa những dải hình cho npc
| `EnemySheet` | Dải hình kẻ địch | Chứa những hình ảnh của kẻ địch trong game 
| `ParticleSheet` | Dải hình hiệu ứng | Chứa những dải hình cho các hiệu ứng cháy, nổ, nước bantumlum
| `PauseScreen` | Hình tạm ngưng | Chứa những hình nền, nút bấm ở màn hình tạm ngưng game 
| `PopupBubble` | Bong bóng hiện hình | Gồm các ô hội thoại hướng dẫn người chơi, cốt truyện, ...

#### Lưu ý:

- Tất cả các file hình ảnh được lưu dưới định dạng .png 
- Giải thích *dải hình*: là một dải bao gồm nhiều `state` (trạng thái) của một hình động, mỗi một `state` được gán với 1 hình cụ thể của một giải hình


## B. MÃ NGUỒN GAME

- Các header file được lưu trong folder **`include`**

- Các thư viện được lưu trong folder **`libraries`**, bao gồm:
  - SDL2: phụ trách phần nhận `input` và khởi tạo `window`
  - SDL_Image: xử lý hoạt ảnh
  - SFML_Audio: xử lý âm thanh

- Các file `.cpp` được lưu trong folder **`src`** 

## C. THIẾT LẬP GAME

### 1. Cài đặt [`configuration`]

#### Bao quát

- Sử dụng mô hình thiết kế **SINGLETON** đảm bảo sự tồn tại độc nhất vô nhị của bản thân, hạn chế khởi tạo

#### Tái định nghĩa `define` các mảng vector `std::vector`

- Hỗ trợ cho việc tạo mảng dễ dàng hơn.

```cpp
#define int1D std::vector<int> 
#define int2D std::vector<int1D> 

#define float1D std::vector<float> 
#define float2D std::vector<float1D> 

#define long1D std::vector<long> 
#define long2D std::vector<long1D> 

#define bool1D std::vector<bool> 
#define bool2D std::vector<bool1D> 

#define short1D std::vector<short> 
#define short2D std::vector<short1D> 

#define string0D std::string 
#define string1D std::vector<string0D> 
#define string2D std::vector<string1D> 

#define SDLTexture1D std::vector<SDL_Texture*> 
#define SDLTexture2D std::vector<SDLTexture1D>

#define SDLRect1D std::vector<SDL_Rect> 
#define SDLRect2D std::vector<SDLRect1D>
```

#### Giao diện chuyển cảnh `struct TransitionEffect`

- Sử dụng để làm đen màn hình khi di chuyển giữa các menu và khu vực nhất định của mỗi ải

```cpp
struct TransitionEffect 
{ 
    // Hình của màn hình đen
    SDL_Texture *BLACKSCREEN;

    // Các giá trị diễn tả tiến trình của chuyển cảnh
    float side_max = 100; 
    float mid_max = 100; 

    float side_cur = 0;
    float mid_cur = 0;

    // Các giá trị diễn tả trạng thái
    bool active = 0; 
    bool fade = 0;

    // Các hàm cập nhật
    void update(); 
    void set(float s, float m, bool skipStart = 0);

    // Các điểm kích hoạt
    bool leftactive();
    bool rightactive();
    bool midpoint(); 
};
```

- `Transition` chuyển cảnh bao gồm 3 quá trình
    - Làm đen màn hình
    - Giữ nguyên màn hình đen (dành cho việc thực hiện các thuật toán trong quá trình màn hình đen)
    - Làm sáng màn hình

#### Lớp cài đặt `class Configuration`

##### Thành phần:

- Chứa các thông tin cài đặt của game:
  - Độ phân giải cửa sổ
  - FPS (Frame per second)
  - Trạng thái menu
  - EVENT (sự kiện)
  - ...

- Chứa các phương thức làm việc với cửa sổ

- Chứa các công cụ debugging

- Chứa các phương thức làm việc với `string` và `vector` để các vật thể `object2D` khác có thể truy cập dễ dàng

```cpp
class Configuration
{
public: 

    // Các hàm thiết lập/hủy bỏ
    ~Configuration();
    Configuration();

    void postupdate();

    // Trạng thái game
    bool QUIT = 0;
    /* Danh sách
        0: Menu 
        1: Đang chơi 
        2: Tạm dừng
    */
    short STATE = 0; 
    void changeState(); 

    // Thời gian/FPS
    int FPS = 100; 
    long RUNTIME = 0; 
    long WORLDTIME = 0; 
    int DELAY_TIME = 10; 
    void frameHandler(); 

    // Sự kiện
    SDL_Event EVENT;

    // Kích cỡ cửa sổ
    int WIDTH = 1280, HEIGHT = 768; 
    void resizeWindow(int W, int H); 
    void drawFullscreen(SDL_Texture *texture, float whr, short1D position); 

    // Cửa sổ
    SDL_Window *WINDOW = SDL_CreateWindow("Abyssal Hymn", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI); 
    SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, 0); 
    SDL_Surface *ICON = SDL_LoadBMP("assets/icon.bmp"); 

    // Hàm thao túng texture
    SDL_Texture *loadTexture(string0D path); 
    SDLTexture1D loadTextures(string0D path, int max); 

    // Hiệu ứng chuyển cảnh bằng màn hình đen
    TransitionEffect TRANSIT_EFFECT; 

    // Các giá trị/hàm dành cho debug
    string0D PRELOG = ""; 
    string0D DEVLOG = ""; 

    void addDevlog(string0D text, int colorCode); 
    void printDevlog(); 
    static bool isComment(string0D str); 

    // ====== Các hàm thao túng string và vector ====== 

    // Cắt string
    static string1D splitStrVec(string0D file_dir); 

    // 0-Padding: ví dụ: 0 thành 001, 21 thành 021, 121 thành 121... 
    static string0D convertZPad(int number, int maxNumber); 

    // Thay đổi kích cỡ
    static int2D resizeInt2D(int1D vec, int r, int c); 
    static long2D resizeLong2D(long1D vec, int r, int c); 
    static float2D resizeFloat2D(float1D vec, int r, int c); 

    // Chuyển hóa 
    static string1D convertStr1D(string0D str, char delimiter = ',');  
    static int1D convertStrInt1D(string0D str, char delimiter = ','); 
    static long1D convertStrLong1D(string0D str, char delimiter = ','); 
    static float1D convertStrFloat1D(string0D str, char delimiter = ','); 
    static int1D convertFloat1DInt(float1D vec); 
    static int2D convertFloat2DInt(float2D vec); 

    // Cờ bạc
    static int randomInt(int max); 
    static int1D randomInt1D(int max, int min = 0, bool shuffle = 1); 
}; 
```

### 2. Nhập vào [`input`] 

#### Trạng thái phím `struct KeyState`

- Lưu trữ trạng thái của mỗi nút `key`:
  - `press`: nhận bấm 1 lần tức thì, lần thực hiện tiếp xảy ra sau khi thả phím
  - `hold`: thực hiện liên tục chừng nào phím còn giữ
  - `threshold`: tương tự `hold` nhưng chỉ xảy ra sau khi giữ một thời gian nhất định
- Bao gồm hàm trực tiếp thao túng `input` người chơi: `script`

```cpp
struct KeyState 
{ 
    SDL_Scancode code; 

    bool moveset = 1; 
    bool state = 0; 
    bool hold = 0; 

    int prepress; 
    bool press(); 

    int threshold = 0, 
        threspeak = 0; 
    bool threspass(int max); 

    int keydelay = 0;

    void update(const Uint8* state, Input *input); 
    
    // Thao túng
    long1D script; 
    long1D script_history; 
    string0D scriptHistoryToStr(); 
};
```

#### Phím mặc định `struct KeyTemplate<TempIndex>`

- Chứa các cài đặt nút điều khiển mặc định.

```cpp
struct KeyTemplate<TempIndex>
{
    KeyState 
        moveU = {<KeyCode>}, 
        moveD = {<KeyCode>}, 
        moveL = {<KeyCode>}, 
        moveR = {<KeyCode>}, 
        proj = {<KeyCode>}, 
        equip = {<KeyCode>}, 
        attack = {<KeyCode>}, 
        jump = {<KeyCode>}, 
        dash = {<KeyCode>};
};
```

#### Trạng thái chuột `struct MouseState`

- Xử lý trạng thái nút chuột, tương tự `KeyState`.

```cpp
struct MouseState 
{
    int button = 0;
    bool state = 0;
    bool hold = 0;

    bool click();

    int threshold = 0,
        threspeak = 0;

    bool threspass(int max); 
    void update(Uint32 mousestate); 
};
```

#### Xử lý chuột `struct MouseMain`

- Gồm trạng thái chuột `MouseState` cho chuột trái/phải/giữa, vị trí chuột `x, y` và con lăn `W`
- Gồm các hàm tính vị trí chuột trên màn hình và vị trí tương đối so với `player` / `map`

```cpp
struct MouseMain 
{
    MouseState 
        // LEFT MOUSE 
        L = {SDL_BUTTON_LEFT}, 
        // MIDDLE MOUSE 
        M = {SDL_BUTTON_MIDDLE}, 
        // RIGHT MOUSE 
        R = {SDL_BUTTON_RIGHT}; 

    short W = 0; 
    int x = 0, y = 0; 

    void update(); 

    int offMidX(); 
    int offMidY(); 
    int offPlayerX(Player *player); 
    int offPlayerY(Player *player); 
    int mapX(Player *player, short grid = 64); 
    int mapY(Player *player, short grid = 64); 
    bool inbox(ObjectBox mbox);
};
```

#### Xử lý `input` tổng bộ

- Bao gồm các phím `key` và chuột `mouse`. Các nút bấm được tạo ra từ `keystate` sử dụng `keytemplate` cho các hành động cho người chơi, kèm theo các phím bổ sung
- Gồm hàm thực hiện việc thao túng `input` của người chơi, dành cho những người chơi có hứng thú với việc tạo ra một run chơi hoàn hảo như TAS (Tool Assist Speedrun)

```cpp
class Input 
{
public:
// ============================= KEYSTATE =======================

	KeyState
		// Gameplay
		moveU, moveD, moveL, moveR,
		proj, equip, attack,
		jump, dash,

		// Other
		lalt = {SDL_SCANCODE_LALT, 0},
		lctrl = {SDL_SCANCODE_LCTRL, 0},
		lshift = {SDL_SCANCODE_LSHIFT, 0},

		space = {SDL_SCANCODE_SPACE, 0},
		backspace = {SDL_SCANCODE_BACKSPACE, 0},

		arrowU = {SDL_SCANCODE_UP, 0},
		arrowD = {SDL_SCANCODE_DOWN, 0},
		arrowL = {SDL_SCANCODE_LEFT, 0},
		arrowR = {SDL_SCANCODE_RIGHT, 0},

		slash = {SDL_SCANCODE_SLASH, 0},
		backslash = {SDL_SCANCODE_BACKSLASH, 0},

		escape = {SDL_SCANCODE_ESCAPE, 0},

		// Function Key
		f1 = {SDL_SCANCODE_F1, 0},
		f2 = {SDL_SCANCODE_F2, 0},
		f3 = {SDL_SCANCODE_F3, 0},
		f4 = {SDL_SCANCODE_F4, 0},
		f5 = {SDL_SCANCODE_F5, 0},
		f6 = {SDL_SCANCODE_F6, 0};

	string0D script_history_full = "";
	bool script_active = 0;

	MouseMain mouse;

	int delay = 0;

	Input();
	void setTemplate(int keytemplate);
	void update();
	void executeScript(string0D script_dir, bool from_cur = 0);
	void endScript();

	SDL_GameController *controller;
};
```

### 3. Âm thanh [`audio`]

#### Hiệu ứng âm thanh `struct AudioSFX`

- Chứa một âm thanh ngắn có thể lặp đi lặp lại theo ý muốn

```cpp
struct AudioSFX {
    sf::SoundBuffer buffer;
    sf::Sound sound;

    AudioSFX(const std::string& filePath);
    void play();
    bool isPlaying();
    static void shuffle(AudioSFX1D &sfx);
};
```

#### Danh sách âm thanh nền

- Chứa một danh sách âm thanh `AudioPlaylist`, chơi theo một thứ tự lần lượt/ngẫu nhiên (dựa trên cài đặt của người chơi) với một khoảng `delay` bất kỳ
- Bao gồm các hàm phụ trách trạng thái và âm lượng của `Audio`

```cpp
// Danh sách âm thanh
struct AudioPlaylist
{
    string1D paths;
    int1D delays;
    bool random = 0;

    // Music Track
    int m_cur = 0;
    int1D m_list;

    int delay = 0;

    void updatePlaylist(bool fresh = 0);
    bool comparePlaylist(AudioPlaylist other);
};

// Chơi danh sách đó
class Audio
{
private:
    bool stop = 0;
    // Volume
    int vol_cur = 100;
    int vol_max = 100;

    AudioPlaylist playlist;
    sf::Music music_cur;

public:
    ~Audio();
    Audio();

    // ============== BACKGROUND MUSIC ==============

    // Music Playlist
    void createPlaylist(AudioPlaylist alb);
    // Current Music
    void setPlistStop(bool s);
    void setPlistVolCur(int v);
    void setPlistVolMax(int v);
    bool getPlistStop();
    int getPlistVolCur();
    int getPlistVolMax();

    void updateTrack();
    static void appendMapPlaylist(Map *map, string0D t_dir);

    static bool isMusicPlaying(sf::Music &music);
    static bool isSoundPlaying(sf::Sound &sound);
};
```

### 4. Tạo hình [`renderer`]

#### Quản lý các phương thức vẽ

- Phụ trách cho việc vẽ mọi vật lên màn hình theo một trình tự nhất định:
  - Khởi tạo màu nền
  - Vẽ hình nền
  - Vẽ khối nền
  - Vẽ trang trí nền
  - Vẽ cửa
  - Vẽ hiệu ứng
  - Vẽ địch
  - Vẽ người chơi
  - Vẽ đạn
  - Vẽ khối chính
  - Vẽ khối ẩn (sẽ giải thích ở phần [`block`] sắp tới)
  - Vẽ ô hội thoại
  - Vẽ trang trí trước mặt
  - Vẽ hiệu ứng trước mặt
  - Vẽ hud

```cpp
class Renderer
{
public:
    void renderGameplay(Map *map);
};
```

- Lưu ý: hàm `renderGameplay` sẽ phụ trách phần vẽ và **CHỈ PHẦN VẼ**, các hàm liên quan đến việc cập nhật thuật toán phức tạp như di chuyển sẽ không bao gồm trong này nhằm phân chia nguồn lực thích hợp, tránh việc hình vẽ bị thiếu đồng bộ.

### 5. Vật thể 2D [`object2D`]

#### Bao quát

- 1 Abstract Class, Superclass của mọi vật thể 2D trong game (người chơi, hiệu ứng, địch, ...)

#### Các thuộc tính

- Các thuộc tính của vật thể được chia làm 3 thành phần chính:
  - `ObjectHitbox`: gồm tọa độ `x, y`, kích cỡ `w, h` và hitbox `hw, hh`
  - `ObjectMovement`: phụ trách cho hoạt động di chuyển của vật thể gồm vật tốc: `vel_x, vel_y` và gia tốc `accel_x, accel_y`
  - `ObjectSprite`: phụ trách cho hoạt hình của vật thể, là thành phần cần thiết với các vật thể sử dụng dải hình

- Gồm các `struct` bổ sung nhằm dễ dàng khởi tạo cũng như gán một số giá trị vào

#### Các thành phần bổ sung

- Các `struct` bổ sung để gói gọn những yếu tố cụ thể của một vật thể:
  - Các `ObjectHitbox`, `ObjectMovement`, `ObjectSprite` kể trên
  - `ObjectBox`: một hộp phụ trách cho tương tác
  - `ObjectXY<datatype>`: chứa 2 biến `x, y` phục vụ mục đích tự do
  - `ObjectCombatBox`: một hộp dành riêng cho mục đích tấn công

#### Các phương thức

- `getter` và `setter` cho tất cả các thuộc tính được kể trên
- Các phương thức tĩnh tính khoảng cách `distX(), distY(), distR()` cũng như tương tác giữa các vật thể 
- Các phương thức quản lý tiến trình vẽ dải hình của vật thể `setSprite()`
- Các phương thức phụ trách cho việc tấn công
- Các phương thức tạo/xóa `texture`

```cpp
class Object2D
{
private:
    int special_key = -1;

    // Size and position
    float x = 0, y = 0;
    int width = 0,
        height = 0;
    int hit_w = 0,
        hit_h = 0;

    // Speed
    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;

    // Combat (if possible)
    int combat_hit_up = 0;
    int combat_hit_down = 0;
    int combat_hit_left = 0;
    int combat_hit_right = 0;
    int combat_damage = 0;

    // Sprites handling
    int sprite_index = 0,
        sprite_index_max = 0;
    int sprite_row = 0,
        sprite_row_max = 0,
        sprite_row_repeat = 0;
    int sprite_frame = 0,
        sprite_frame_max = 0;
    int sprite_width = 0,
        sprite_height = 0;

    // Ignore Object Existance
    bool ignore = 0;

    // Camera Dependencey
    bool cam_depend = true;

public:
    ~Object2D(); // Default Destructor
    Object2D(); // Default Constructor
    Object2D(ObjectHitbox box, ObjectSprite sprite = {}, ObjectMovement movement = {});
    Object2D(float X, float Y, int w, int h);
    Object2D(float X, float Y, int w, int h, int hw, int hh);
    Object2D(float X, float Y, int w, int h, int hw, int hh,
            int sw, int sh, int sim, int sfm, int si = 0, int sf = 0);

    // Ignore Drawing
    bool getIgnore();
    void setIgnore(bool ignore);

    // Camera Independent
    bool getCamDepend();
    void setCamDepend(bool depend);

    // Position
    void setX(float X);
    void setY(float Y);
    float getX();
    float hitbox.y;
    int hitbox.gridX();
    int hitbox.gridY();
    int getGridLX();
    int getGridRX();
    int getGridTY();
    int getGridBY();

    // Size / Hitbox
    void setWidth(int w);
    void setHeight(int h);
    void setHitWidth(int hw);
    void setHitHeight(int hh);
    int hitbox.w;
    int hitbox.h;
    int getGridWidth(bool getExtend = 0);
    int getGridHeight(bool getExtend = 0);
    int getHitWidth();
    int getHitHeight();

    // Comabt hitbox
    void setCombatHit(ObjectCombatBox c_hit);
    void setCombatHitU(int hit);
    void setCombatHitD(int hit);
    void setCombatHitL(int hit);
    void setCombatHitR(int hit);
    void setCombatDamage(int dmg);
    ObjectCombatBox getCombatHit();
    int getCombatHitU();
    int getCombatHitD();
    int getCombatHitL();
    int getCombatHitR();
    int getCombatDamage();

    // Speed / Accelaration

    // Simple movement, no extra logic
    void setVelX(float velX);
    void setVelY(float velY);
    void setAccelX(float accX);
    void setAccelY(float accY);
    float getVelX();
    float getVelY();
    float getAccelX();
    float getAccelY();

    // Drawing
    void setSprWidth(int sw);
    void setSprHeight(int sh);
    void setSprIndex(int si);
    void setSprIndexMax(int sim);
    void setSprRow(int sr);
    void setSprRowMax(int srm);
    void setSprRowRepeat(int srr);
    void setSprFrame(int sf);
    void setSprFrameMax(int sfm);
    int sprite.sw;
    int sprite.sh;
    int sprite.si;
    int sprite.sim;
    int sprite.sr;
    int getSprRowMax();
    int getSprRowRepeat();
    int getSprFrame();
    int sprite.sfm;

    // Box
    bool insideBox(ObjectBox box);
    bool insideGridBox(ObjectBox gridbox);
    ObjectBox getBox();

    // Special Key for customizable value
    void setSpecialKey(int key);
    int getSpecialKey();

    // =================== VERY HELPFUL METHOD ======================

    // Note!!!: dist is a vector in both direction,
    // not the absolute value
    static int distX(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distY(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distBorderX(Object2D *obj1, Object2D *obj2);
    static int distBorderY(Object2D *obj1, Object2D *obj2);
    static int distR(Object2D *obj1, Object2D *obj2);

    static ObjectBox SDLRectToBox(SDL_Rect rect);
    static SDL_Rect BoxToSDLRect(ObjectBox box);

    static bool objectIgnore(Object2D *objMain, Object2D *objSub);

    static void deleteTextures(SDLTexture1D textures);

    bool setSprite(bool end_lock = 0);
    static void objectSetSprite(ObjectSprite &sprite);

    void objectStandardMovement(bool lock_vel = 0);
    float1D objectPredictMovement();
};
```

class Multiplayer 

{ 

public: 

    Player1D Players; 

    Player *MAIN; 

    int PlayerCount = 0; 

    ~Multiplayer(); 

    Multiplayer(Player1D players); 

     

    // Player Count Control 

    void addPlayer(); 

    void changeMain(int index); 

    void singlePlayer(); 

    void update(Map *map); 

    void drawPlayers(); 

    void drawHuds(); 

}; 

object2D.h 

+ Class Object2D là 1 abstract class, superclass của mọi vật thể 2D trong game (người chơi, block, kẻ địch, trang trí, đạn, cửa, vật thể âm thanh, ô hội thoại, hiệu ứng). 

+ Các thuộc tính của lớp bao gồm:  

Tọa độ x, y, kích cỡ rộng, cao thường và của hitbox. 

Tốc độ, gia tốc. 

Các biến combat. 

Những giá trị kích cỡ rộng, cao của sprite trên sprite sheet, sprite index cho sheet (hỗ trợ di chuyển giữa 1 hoạt ảnh trong sheet sang hoạt ảnh tiếp theo), và sprite frame (số frame mà hoạt ảnh này được in trên màn hình). 

Tính phụ thuộc vào camera của vật (boolean). 

+ Các phương thức bao gồm: 

Getter, setter cho tất cả các thuộc tính trên. 

Trả về giá trị bool khi vật ở trong khu vực box, gridbox nhất định 

Các phương thức tĩnh trả về khoảng cách vector giữa x, y 2 vật hoặc x, y ở rìa 2 vật. 

Các phương thức tĩnh biến ObjectBox thành SDL_rect và ngược lại (Hỗ trợ việc tạo box và xác định vị trí box). 

Phương thức tĩnh giúp 2 vật không tương tác với nhau. 

Phương thức tĩnh xóa texture. 

Cài đặt sprite cho vật, cùng phương thức tĩnh. 

Phương thức di chuyển của vật, mảng vector 1 chiều trả về vị trí dự đoán vật sẽ đi qua. 

class Object2D 

{ 

private: 

    int special_key = -1; 

    // Size and position 

    float x = 0, y = 0; 

    int width = 0, 

        height = 0; 

    int hit_w = 0, 

        hit_h = 0; 

    // Speed 

    float vel_x = 0, vel_y = 0; 

    float accel_x = 0, accel_y = 0; 

    // Combat (if possible) 

    int combat_hit_up = 0; 

    int combat_hit_down = 0; 

    int combat_hit_left = 0; 

    int combat_hit_right = 0; 

    int combat_damage = 0; 

    // Sprites handling 

    int sprite_index = 0, 

        sprite_index_max = 0; 

    int sprite_row = 0, 

        sprite_row_max = 0, 

        sprite_row_repeat = 0; 

    int sprite_frame = 0, 

        sprite_frame_max = 0; 

    int sprite_width = 0, 

        sprite_height = 0; 

    // Ignore Object Existance 

    bool ignore = 0; 

    // Camera Dependencey 

    bool cam_depend = true; 

public: 

    ~Object2D(); // Default Destructor 

    Object2D(); // Default Constructor 

    Object2D(ObjectHitbox box, ObjectSprite sprite = {}, ObjectMovement movement = {}); 

    Object2D(float X, float Y, int w, int h); 

    Object2D(float X, float Y, int w, int h, int hw, int hh); 

    Object2D(float X, float Y, int w, int h, int hw, int hh, 

            int sw, int sh, int sim, int sfm, int si = 0, int sf = 0); 

    // Ignore Drawing 

    bool getIgnore(); 

    void setIgnore(bool ignore); 

    // Camera Independent 

    bool getCamDepend(); 

    void setCamDepend(bool depend); 

    // Position 

    void setX(float X); 

    void setY(float Y); 

    float getX(); 

    float hitbox.y; 

    int hitbox.gridX(); 

    int hitbox.gridY(); 

    int getGridLX(); 

    int getGridRX(); 

    int getGridTY(); 

    int getGridBY(); 

    // Size / Hitbox 

    void setWidth(int w); 

    void setHeight(int h); 

    void setHitWidth(int hw); 

    void setHitHeight(int hh); 

    int hitbox.w; 

    int hitbox.h; 

    int getGridWidth(bool getExtend = 0); 

    int getGridHeight(bool getExtend = 0); 

    int getHitWidth(); 

    int getHitHeight(); 

    // Comabt hitbox 

    void setCombatHit(ObjectCombatBox c_hit); 

    void setCombatHitU(int hit); 

    void setCombatHitD(int hit); 

    void setCombatHitL(int hit); 

    void setCombatHitR(int hit); 

    void setCombatDamage(int dmg); 

    ObjectCombatBox getCombatHit(); 

    int getCombatHitU(); 

    int getCombatHitD(); 

    int getCombatHitL(); 

    int getCombatHitR(); 

    int getCombatDamage(); 

    // Speed / Accelaration 

    // Simple movement, no extra logic 

    void setVelX(float velX); 

    void setVelY(float velY); 

    void setAccelX(float accX); 

    void setAccelY(float accY); 

    float getVelX(); 

    float getVelY(); 

    float getAccelX(); 

    float getAccelY(); 

    // Drawing 

    void setSprWidth(int sw); 

    void setSprHeight(int sh); 

    void setSprIndex(int si); 

    void setSprIndexMax(int sim); 

    void setSprRow(int sr); 

    void setSprRowMax(int srm); 

    void setSprRowRepeat(int srr); 

    void setSprFrame(int sf); 

    void setSprFrameMax(int sfm); 

    int sprite.sw; 

    int sprite.sh; 

    int sprite.si; 

    int sprite.sim; 

    int sprite.sr; 

    int getSprRowMax(); 

    int getSprRowRepeat(); 

    int getSprFrame(); 

    int sprite.sfm; 

    // Box 

    bool insideBox(ObjectBox box); 

    bool insideGridBox(ObjectBox gridbox); 

    ObjectBox getBox(); 

    // Special Key for customizable value 

    void setSpecialKey(int key); 

    int getSpecialKey(); 

    // =================== VERY HELPFUL METHOD ====================== 

    // Note!!!: dist is a vector in both direction, 

    // not the absolute value 

    static int distX(Object2D *obj1, Object2D *obj2, bool absolute = 0); 

    static int distY(Object2D *obj1, Object2D *obj2, bool absolute = 0); 

    static int distBorderX(Object2D *obj1, Object2D *obj2); 

    static int distBorderY(Object2D *obj1, Object2D *obj2); 

    static int distR(Object2D *obj1, Object2D *obj2); 

    static ObjectBox SDLRectToBox(SDL_Rect rect); 

    static SDL_Rect BoxToSDLRect(ObjectBox box); 

    static bool objectIgnore(Object2D *objMain, Object2D *objSub); 

    static void deleteTextures(SDLTexture1D textures); 

    bool setSprite(bool end_lock = 0); 

    static void objectSetSprite(ObjectSprite &sprite); 

    void objectStandardMovement(bool lock_vel = 0); 

    float1D objectPredictMovement(); 

}; 

+ struct ObjectXY, struct ObjectXYb, struct ObjectXYs, struct ObjectXYf, struct ObjectXYWH, đều chứa tọa độ x, y của object, với b, s, f được dùng để xác định kiểu dữ liệu của x và y của mỗi struct. ObjectXYWH còn bao gồm thêm chiều rộng và chiều cao của vật. 

struct ObjectXY { int x = 0, y = 0; }; 

struct ObjectXYb { bool x = 0, y = 0; }; 

struct ObjectXYs { short x = 0, y = 0; }; 

struct ObjectXYf { float x = 0, y = 0; }; 

struct ObjectXYWH { int x = 0, y = 0, w = 0, h = 0; }; 

+ struct ObjectHitBox chứa tọa độ x, y, chiều rộng, chiều cao, chiều rộng hitbox, chiều cao hitbox, kích cỡ grid (mặc định là 64) 

struct ObjectHitbox 

{ 

    float x = 0, y = 0; 

    float w = 0, h = 0; 

    int hw = w, hh = h; 

    ObjectHitbox hitboxGrid(int gr = 64); 

    void grid(int gr = 64); 

}; 

+ struct ObjectBox 

struct ObjectBox 

{  

    int up = -1, down = -1, 

        left = -1, right = -1; 

    // Some Method 

    ObjectBox boxGrid(int gr = 64); 

    void grid(int gr = 64); 

    void reorder(); 

    void copy(ObjectBox box); 

    bool compare(ObjectBox box); 

    bool contain(int x, int y); 

    ObjectHitbox hitbox(); 

}; 

+ struct ObjectCombatBox 

struct ObjectCombatBox 

{ int up = 0, down = 0, left = 0, right = 0, dmg = 0; }; 

+ struct ObjectSprite chứa những giá trị kích cỡ rộng, cao của sprite trên sprite sheet, sprite index cho sheet (hỗ trợ di chuyển giữa 1 hoạt ảnh trong sheet sang hoạt ảnh tiếp theo), và sprite frame (số frame mà hoạt ảnh này được in trên màn hình). 

struct ObjectSprite 

{ 

    int sw = 0, sh = 0; 

    int sim = 0, sfm = 0; 

    int si = 0, sf = 0; 

}; 

+ struct ObjectMovement chứa các biến vận tốc x, y, gia tốc x, y. 

struct ObjectMovement 

{ 

    float vel_x = 0, vel_y = 0; 

    float accel_x = 0, accel_y = 0; 

}; 

	+ class Object2D chứa các thuộc tính  