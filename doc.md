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
- Giải thích *dải hình*: là một dải bao gồm nhiều `state` (trạng thái) của một hình động, mỗi một `state` được gán với 1 *hình* cụ thể của *giải hình* đó

## B. MÃ NGUỒN GAME

- Các header file được lưu trong folder **`include`**

- Các thư viện được lưu trong folder **`libraries`**, bao gồm:
  - SDL2: phụ trách phần nhận `input` và khởi tạo `window`
  - SDL_Image: xử lý hoạt ảnh
  - SFML_Audio: xử lý âm thanh

- Các file `.cpp` được lưu trong folder **`src`** 

## C. THÀNH PHẦN CHỦ TRÌ

- Là các thành phần mang tính chất cài đặt, là tiền đề cho sự tồn tại của các thành phần nội dung

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

#### Danh sách âm thanh nền `struct AudioPlaylist`

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
- Các phương thức tĩnh tính khoảng cách `distX(), distY(), distR()` cũng như tương tác giữa các `ObjectBox`
- Các phương thức quản lý tiến trình vẽ dải hình của vật thể `setSprite()`
- Các phương thức phụ trách cho việc tấn công
- Các phương thức tạo/xóa `texture`

```cpp
class Object2D
{
public:
    int special_key = -1;

    // Size and position
    ObjectHitbox hitbox;
    // Sprite
    ObjectSprite sprite;
    // Movement
    ObjectVel vel;
    ObjectAccel accel;

    // Combat (if possible)
    ObjectCombatBox combatbox;

    // Ignore Object Existance
    bool ignore = 0;
    // Camera Dependencey
    bool cam_depend = 1;

    ~Object2D(); // Default Destructor
    Object2D(); // Default Constructor
    Object2D(ObjectHitbox box, ObjectSprite spr = {}, ObjectVel v = {}, ObjectAccel a = {});

    // Box
    bool insideBox(ObjectBox box);
    bool insideGridBox(ObjectBox gridbox);
    ObjectBox getBox();

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

### 6. Bản đồ [`map`]

#### Thông tin map `struct MapInfo`

- Gồm các thông tin liên quan đến map như tên map, độ khó, hình nền chủ đạo, ...

```cpp
struct MapInformation
{
    string0D name = "";
    string0D difficulty = "";

    SDL_Texture *pause_bg = CFG->loadTexture(
        "assets/PauseScreen/Default.png"
    );
    float pause_ratio = 1.77;

    void readInfo(string0D dir);
    void clearInfo();
};
```

#### Thành phần map `struct MapComponent`

- Gồm các thành phần động tương tác với map như khối `block`, thực thể `entity` như người chơi `player` với địch `enemy`, hình nền `background`, trang trí `decoration`, ...
- Các thành phần của map được gói bên trong một `std::vector<COMPONENT>` tương ứng với các thành phần đó
- Gồm các hàm thao túng sự tồn tại của các vật thể, với hàm xóa địa chỉ bộ nhớ động `*pointer` triệt để

```cpp
struct MapComponent
{
    Map *map;
    // Directory
    string0D 
        map_dir = "",
        playlist = "",
        block_path = "",
        block_main = "",
        block_back = "",
        block_hidden = "",
        background = "",
        decor_back = "",
        decor_front = "",
        door = "",
        bubble = "",
        enemy = "",
        item = "",
        audio_obj = "",
        camera_box = "",
        transit_map = "";

    void appendDirectory();
    void appendComponent();
    void clearComponent();

    // Append specific
    void appendPlaylist();
    void appendBlockPath();
    void appendBlockMain();
    void appendBlockHidden();
    void appendBlockBack();
    void appendBackground();
    void appendDecorBack();
    void appendDecorFront();
    void appendDoor();
    void appendBubble();
    void appendEnemy();
    void appendItem();
    void appendAudioObj();
    void appendCameraBox();
    void appendTransitMap();

    // Clear specific
    void clearPlaylist();
    void clearBlockPath();
    void clearBlockMain();
    void clearBlockHidden();
    void clearBlockBack();
    void clearBackground();
    void clearDecorBack();
    void clearDecorFront();
    void clearDoor();
    void clearBubble();
    void clearEnemy();
    void clearItem();
    void clearAudioObj();
    void clearCameraBox();
    void clearTransitMap();

    // Delete specific
    void eraseBlockMain(int i);
    void eraseBlockBack(int i);
    void eraseBlockHidden(int i);
    void eraseBackground(int i);
    void eraseDecorBack(int i);
    void eraseDecorFront(int i);
    void eraseDoor(int i);
    void eraseBubble(int i);
    void eraseEnemy(int i);
    void eraseItem(int i);
    void eraseAudioObj(int i);
    void eraseCameraBox(int i);
    void eraseTransitMap(int i);
};
```

#### Lớp Map tổng bộ `class Map`

- Gồm `MapInfo` với `MapComponent` cùng với các thành phần động của map
- Gồm các hàm khởi tạo thành phần động bằng phương thức đọc file `append<COMPONENT>(string0D địa_chỉ_file_csv_của_thành_phần)`
- Gồm các phương thức khởi tạo `init<_>` và cập nhật `update<_>`
- Các phương thức `init<_>` và `update<_>` sẽ tồn tại dưới dạng:
  - `<Global>`: phương thức được thực hiện ở mọi thời điểm mặc cho việc `player` không có mặt trong `map`
  - `<Active>`: phương thức chỉ thực hiện với sự có mặt của `player` trong `map`

```cpp
class Map
{
public:
    // ======== STATE ================
    bool Active = 0;

    // ======== DEFAULT ==============
    World *WORLD;
    Audio *AUDIO;
    Collision *COLLI;
    Multiplayer *MULTI;

    // ======== MAP INFO =============
    MapInformation MapInfo;

    // ======== MAP COMPONENT ========
    // COMPONENT HANDLER
    MapComponent MapComp;
    // Music Album
    AudioPlaylist MapPlaylist;
    // Block Path
    string1D BlockPath;
    // Block Preview Texture
    SDLTexture1D BlockPreview;
    // Enemy
    Enemy1D EnemyVec;
    // Npc
    Bubble1D BubbleVec;
    // Particle_Effect
    Particle1D ParticleBackVec;
    Particle1D ParticleFrontVec;
    // Block
    Block1D BlockMainVec;
    Block1D BlockBackVec;
    Block2D BlockHiddenVec;
    // Yuki Makoto
    Door1D DoorVec;
    // Item
    Item1D ItemVec;
    // Cosmetic
    MapBgColor MapColor;
    Decoration1D BackgroundVec;
    Decoration1D DecorBackVec;
    Decoration1D DecorFrontVec;
    // Projectile
    Projectile1D ProjectileVec;
    // AUDIO SOURCE
    AudioObj1D AudioObjVec;
    // Exclusive update function
    ExclusiveUpdate UpdateExclusive = [](Map *map) {};

    // ======== MAP INTERACTION ========
    bool OutsideRender = 0;
    CameraBox1D CameraBox;
    MapTransit1D TransitMap;

    // =================== Stage stuff idc ===================

    ~Map();
    Map(string0D mapname);

    void initMap(World *world, Multiplayer *multi, Audio *audio,
                Collision *collision, int id = -1);
    void initMapStandard();

    void updateMapActive();
    void updateMapGlobal();

    // ================== MAP ... IDK WHAT ALGORITHM =====================

    void loadCheckpoint(WorldLocation location);
    void appendTransitMap(string0D trans_dir);
    void appendCameraBox(string0D cam_dir);

    void appendParticle(ParticleEffect *particle, bool front = 0);
};
```

### 7. Đa người chơi [`multiplayer`]

- Gồm một vector chứa các người chơi `std::vector<Player *>`
- Gồm các phương thức điều khiển số lượng / vai trò của người chơi
  - `addPlayer()`, `singlePlayer()`: thao túng số lượng người chơi
  - `changeMain()`: thay đổi người chơi chính
- Gồm hàm cập nhật các người chơi `updatePlayer()`
- Gồm hàm vẽ người chơi `drawPlayers()` và vẽ hiển thị trực quan (các thông số như máu, năng lượng, ...) `drawHuds()`

### 8. Va chạm [`collision`]

- Một class xử lý sự tương tác va chạm của các người chơi `players` đối với các thành phần:
  - Khối hộp `block`
  - Kẻ địch `enemy`
  - Vật phẩm `item` (*WIP*)
- Gồm các phương thức liên quan tới tấn công `combat` và tương tác của các vật thể `object2D` nói chung

```cpp
class Collision
{
public:
    static bool combatCollision(Object2D *attacker, Object2D *receiver, int1D offset = {0, 0});
    static bool playerCombatCollision(Player *player, Object2D *receiver, bool isReceiver = 0);
    
    static bool playerCollision(Player *player, Object2D *obj, int1D offset = {0, 0});

    static bool objectCollision(Object2D *obj1, Object2D *obj2, int1D offset = {0, 0});
    static bool hitboxCollision(ObjectHitbox hbox1, ObjectHitbox hbox2, int1D offset = {0, 0});
    static bool boxCollision(ObjectBox box1, ObjectBox box2, int1D offset = {0, 0});

    // Phần cập nhật va chạm chính 
    void playerBlockCollision(Map *map, Player *player);
    void playerEnemyCollision(Map *map, Player *player);
    void playerItemCollision(Map *map, Player *player);
    void playerUpdateCollision(Map *map, Player *player);
};
```

### 9. Camera động [`camera`]

- Một class sử dụng để vẽ các vật thể tương đối với vị trí của người chơi, đồng thời kiểm tra các vật nằm ngoài giới hạn màn hình / camera

```cpp
class Camera
{
public:
    // For drawing object relative to player
    static int objectDrawX(Player *player, Object2D *obj);
    static int objectDrawY(Player *player, Object2D *obj);

    // Object outside screen
    static bool outOfBound(SDL_Rect desRect);
    static bool outOfCam(Player *player, Object2D *obj);
};
```

## D. THÀNH PHẦN NỘI DUNG

- Là các thành phần cụ thể của game, đặt sự quan trọng về tính nội dung cũng như tính năng

### 0. Lưu ý

- Các thành phần nội dung thường tồn tại bên trong một `std::vector` của `map` nên được định nghĩa `define` như sau:
  - Giả sử: `class Block` $\rightarrow$ `#define std::vector<Block*> Block1D`

### 1. Người chơi [`Player`]

- Ngôi sao và tâm điểm của cuộc chơi, người chơi là thành phần thực thể `entity` có lượng logic dày đặc và phức tạp nhất game. Các hành động của người chơi vượt xa di chuyển đơn giản của những con game platformer nửa mùa với chỉ mỗi khả năng đi, nhảy đơn thuần
- `Player` kế thừa các đặc tính của `Object2D`
- Các hành động, trạng thái của người chơi được gói gọn trong các `struct Player<feature>` đặc trưng cho 1 đặc tính của người chơi

#### $\star$ Các đặc tính của người chơi:

##### # `struct PlayerState`

- Các trạng thái với môi trường của người chơi, cùng với các điều kiện đặc biệt xảy ra từ sự tương tác với môi trường (giả sử: điều kiện <người chơi nhảy khi đang chạy trên băng> sẽ <nhảy thấp hơn nhưng xa hơn>)

```cpp
struct PlayerState
{
    bool on_ground = 0;
    bool on_ice = 0;
    bool in_water = 0;
    short hug_wall = 0;
    bool crawl_lock = 0;

    // Special Condition
    bool jump_on_ice = 0;

    void resetState();
};
```

##### # `struct PlayerMoveset`

- Trạng thái các kỹ năng của người chơi, mở/khóa

```cpp
struct PlayerMoveset
{
    bool move = 1;
    bool jump = 1;
    bool crawl = 1;
    bool g_dash = 1;
    bool a_dash = 1;
    bool hug_wall = 1;

    void enableAll();
    void disableAll();
};
```

##### # `struct PlayerMove`

- Sự di chuyển của người chơi trên trục Ox (hướng ngang trái phải) với các giá trị thao túng vận tốc, gia tốc cũng như hitbox

```cpp
struct PlayerMoving
{
    Player *player;
    // MOVING
    int decel = 0;
    float vel_max = 5;
    int vel_over_time = 0, // Time you spent over the speed cap
        vel_over_max = 100; // Max time before speed corretion
    float vel_jump_saved = 0;
    // CRAWLING
    bool crawl = 0;
    float vel_crawl = .8;
    int hit_offset_x = 0;
    int hit_offset_y = 0;

    int hitX();
    int hitY();
};
```

##### # `struct PlayerJump`

- Sự di chuyển của người chơi trên trục Oy (hướng dọc trên dưới) với các giá trị thao túng vận tốc, gia tốc trọng trường, độ cao của nhảy, độ cao trần nhà, và cả Coyote Jump (một phương thức phổ biến sử dụng trong game platformer nhằm tạo sự khoan dung cho độ khó trò chơi bằng cách tha thứ cho những input chậm của người chơi)

```cpp
struct PlayerJumping
{
    Player *player;
    // Jumping
    int cur = 0,
        max = 2;
    float terminal = -10;
    // SUPER JUMPING
    int super = 0;
    int super_max = 80;
    // Coyote jump (forgiving jump)
    int coyote = 0;
    int coyote_max = 15;
    bool coyote_fail = 0;

    // Ceiling lock jump
    int ceiling_min = 10;
    int knockout = 0;
    int knockout_delay = 50;
};
```

##### # `struct PlayerADash` và `struct PlayerGDash`

- Hai kỹ năng của người chơi cho phép tăng tốc đột biến theo hướng ngang nhằm né tránh kẻ thù và khám phá map một cách thoải mái hơn, bao gồm các giá trị thời gian, độ trễ, ...

```cpp
struct PlayerAirDash
{
    Player *player;
    // 1 : lock right, -1 : lock left
    short lock = 0;
    int cur = 0;
    int max = 1;
    int frame = 0;
};

struct PlayerGroundDash
{
    Player *player;
    bool super = 0;
    int frame = 0;
    int delay = 0;
};
```

##### # `struct PlayerCombat`

- Trạng thái tấn công của người chơi, với các moveset combat cực kỳ linh hoạt cho phép thực hiện các đòn đánh theo một trình tự cũng như khả năng thay đổi đòn đánh dựa trên môi trường, trạng thái hiện tại người chơi, đấm vỡ mồm lũ sao đỏ Atralis

```cpp
struct PlayerCombat
{
    Player *player;
    // Invincibility (is when you are god)
    int invincible = 0;
    // Invulnerability (is when you get hurt)
    int invulnerable = 0;
    int invulnerable_max = 150;

    // Weapon handler
    bool weapon_equip = 0;
    int weapon_equip_frame = 0; // Only use for drawing
    int weapon_equip_delay = 0;
    int weapon_equip_delay_max = 200;

    int index = 0;
    float time = 0; 
    float combo_time = 0;
    int charge_time = 0;
    float delay = 0; 
    float parry_error = 0;
};
```

##### # `struct PlayerSprite`

- Bao gồm các `texture` cũng như phương thức để vẽ các dải của người chơi một cách dễ dàng hơn

```cpp
struct PlayerSprite
{
    Player *player;
    int index = 0;
    bool right = true;
    bool end_lock = false;
    int alpha = 255;

    SDL_Texture *CurrentTexture,
                *LeftTexture,
                *RightTexture,
                *LeftWeaponTexture,
                *RightWeaponTexture;

    SDL_Rect desRect, srcRect;

    void clearTexture();
    void setSpriteAlpha(int alp);

    void setAct(int idx, bool r);
    void setSprite(int m_index, int m_frame);
    void setEndLock(bool lock);
    void setActSprElock(int1D act, int1D spr, short lock = 0);

    void draw();
    void drawProp();
};
```

##### # `struct PlayerCamera`

- Một chiếc camera linh hoạt với khả năng:
  - Khóa màn hình vào điểm cần chú ý / rìa map
  - Di chuyển tự nhiên với người chơi thay vì khóa một cách cứng nhắc vào tâm màn hình
  - Tạo các hiệu ứng rung, giật như động đất, dash, ...
  - Và nhiều yếu tố thú vị khác ...

```cpp
struct PlayerCamera
{
    Player *player;

    /*
    Mid: Position Based Camera Offset
    - Based on the player's position
    Shift: The Camera Shift (include Effect and Ease)
    - Based on the player's movement
    Center_Off: The Average Position of the Players
    - Based on the number of players

    Offset: The True Camera Offset (include Mid, Shift and Center_Off)
    */

    ObjectXY mid;
    ObjectXY center_off; 
    ObjectXYf focus_trigger;
    ObjectXYb unfocus;
    ObjectXY unfocus_offset;
    ObjectXY offset;

    // Camera Shift Effect
    ObjectXYf shift;
    ObjectXYf ease;
    ObjectXYf effect;

    /*
    Most of the time camera will not snap to the player
    but ease to the player when encounter changes
    */

    // Goal Value
    ObjectBox focus_dir;
    ObjectBox focus_point;
    ObjectBox focus_border;
    bool outside_render = true;
    // Progress Value
    ObjectBox focus_true;
    int focus_speed = 4;
    bool focus_snap = 0;

    ObjectXYf getShift();
    ObjectXY getCenterOffset();
    ObjectXYf getFocusTrigger();

    void setCameraBorder(ObjectBox f_dir, ObjectBox f_val);
    void setCameraFocus(ObjectBox f_dir, ObjectBox f_val, short gr);
    void playerCameraFocus();

    void updateStatic();
    void updateDynamic();
};
```

##### # `struct PlayerSFX`

- Bao gồm các phương thức tạo hiệu ứng âm thanh dựa trên môi trường tương tác người chơi

```cpp
struct PlayerSFX
{
    Player *player;

    // Walking
    int walk_step = 0;
    int walk_sprite = 0;
    int walk_index = 0;
    AudioSFX walk0 = AudioSFX("assets/Audio/PlayerSFX/walk0.mp3");
    AudioSFX walk1 = AudioSFX("assets/Audio/PlayerSFX/walk1.mp3");
    AudioSFX walk2 = AudioSFX("assets/Audio/PlayerSFX/walk2.mp3");
    void updateWalkSFX();

    // Bổ sung sau này ...

    void updateSFX();
};

```

#### Người chơi tổng bộ `class Player`

- Bao gồm các đặc tính kể trên, cùng với các phương thức tạo sự tương tác giữa các đặc tính (Giả sử: Đặc tính đi trên băng trơn `PlayerState.on_ice` sẽ quyết định vận tốc tối đa của `PlayerMove.vel_x_max`)

```cpp
class Player : public Object2D
{
public:
    // Elden ring
    int hp = 100;
    int hp_max = 100;
    int mp = 100;
    int mp_max = 100;

    // ================== META ===================
    bool MAIN;
    int INDEX;
    Input INPUT;
    Hud HUD = Hud(this);
    Multiplayer *MULTI;

    // ================ STATE ====================
    PlayerState state;

    // ============ MOVEMENT/COMBAT ==============
    PlayerMoveset moveset;
    PlayerMoving move = {this};
    PlayerJumping jump = {this};
    PlayerAirDash a_dash = {this};
    PlayerGroundDash g_dash = {this};
    PlayerCombat combat = {this};

    // ============== CAMERA/DRAW ================
    PlayerSprite psprite = {this}; // To avoid conflict with sprite
    PlayerCamera camera = {this};

    // ============== SOUND EFFECT ===============
    PlayerSFX sfx = {this};

    // ============== DEVELOPER ==================
    PlayerDeveloper dev = {this};

    // Constructor
    ~Player();
    Player(bool mc = 0);

    // Stop Player Current State
    void setStatic();

    // ========================= PLAYER LOGIC =========================
    void playerMovement(Map *map);
    void playerCombat(Map *map);
    void playerHitBox();
    void playerGetHit(Map *map, int dmg);
    void playerUpdate(Map *map);
};
```

### 2. Khối hộp [`Block`]

#### Khối nhỏ `struct BlockRect`

- Mỗi một khối hộp được cấu thành từ nhiều khối nhỏ với kích cỡ `64x64`, để quản lý từng khối nhỏ như vậy cần có sự tồn tại của một thành phần mang tên `struct BlockRect` với mục đích lưu giữ thông tin của các khối nhỏ đó: `texture`, `index`, `path`

```cpp
struct BlockRect
{
    SDL_Texture *texture;
    SDL_Rect *rect;
    int index;
    string0D path;
};
```

#### Trạng thái khối `struct BlockState`

- Trạng thái tương tác với người chơi của khối

```cpp
struct BlockState
{
    // Condition
    bool moving = 0;
    bool stepOn = 0;
    short hugged = 0; // -1: left, 1: right
};
```

#### Khối tổng bộ `class Block`

- Gồm `BlockRect` và `BlockState`
- Gồm các thuộc tính đặc trưng của `block` như:
  - Thể loại `type`
  - Độ xuyên thấu `alpha` (dành cho block hiện hình)
- Gồm các thao tác logic

```cpp
class Block : public Object2D
{
public:
    // Sprite handler
    SDLTexture2D textures;
    SDLRect2D rects;
    bool2D noRenders;
    int2D indexs;
    string1D paths;

    // Default
    short grid = 64;
    int seeAlpha = 255;

    // 0:Solid
    // 1:Ice
    // 2:GoThrough
    // 3:Bridge
    // 4:Water
    // 5:SeeThrough
    // 6:TEXTURE
    short type = 0;

    // State
    BlockState state;

    // Condition
    bool can_hug = false;

    // Movement
    float vel_x = 0, vel_y = 0;

    // Developer
    bool highlight = 0;
    SDL_Texture *highlight_texture;
    bool isValid = 1;
    bool needReset = 0;

    ~Block();
    Block();
    // Read From File
    Block(float1D main_val);
    // Simple
    Block(float X, float Y, float w, float h, short type = 0, short gr = 64);
    // Simple (with predefined index)
    Block(float X, float Y, short t, int2D b_index);
    // Block Engine
    void blockEngine(string1D sPath, int2D bIndex = {});

    BlockGrid getGrid();

    void setHighlight(short hl = 2);
    void setBlockIndexs(int2D newIndex);

    void blockSeethrough(Player *player, bool yes = 0);
    void blockCollision(Map *map, Player *player, PlayerState &pState);
    void drawProp(Player *player);
    void draw(Player *player);

    void drawHighlight(Player *player);

    // ============================ BLOCK MANIPULATION =============================

    void refreshTexture(string1D sPath = {});
    void tileEdit(string1D sPath, int1D tIndex, int bIndex);
    void overlap(int2D overlap, int offX, int offY);
};
```

##### $\star$ Phương thức BlockEngine: khởi tạo các block nhỏ rồi ghép chúng với nhau để tạo nên một block hoàn chỉnh

### 3. Thao tác khối hộp [`BlockTemplate`]

- Chứa các phương thức làm việc với `block` như là tách, hợp, kéo dài, so sánh, ...

```cpp
class BlockTemplate
{
private:

public:
    // ================ Block Manipulation =================

    // Get A Column (Why not also Row? Are you fucking stupid)
    static int2D getColumn(int2D vec, int col_index);
    // Split
    static Block1D splitX(Block *block);
    static Block1D splitY(Block *block);
    static Block1D split(Block *block);
    // Compare (for sorting algorithm)
    static bool compareX(Block *block1, Block *block2, bool descend = 0);
    static bool compareY(Block *block1, Block *block2, bool descend = 0);
    // Swap Index
    static void replaceIndex(Block *block, int pre, int post);
    // Expand
    static int2D expandX(int2D original, int cols);
    static int2D expandY(int2D original, int rows);
    // Merge 2 
    static int2D mergeX(int2D vec1, int2D vec2);
    static int2D mergeY(int2D vec1, int2D vec2);
    // Also Merge 2 but more convenient for my fucking console
    static Block *mergeBlockX(Block *blockMain, Block *blockSub);
    static Block *mergeBlockY(Block *blockMain, Block *blockSub);
    // Merge 3
    static int2D mergeX2(int2D vecPre, int2D vecCur, int2D vecPost);
    static int2D mergeY2(int2D vecPre, int2D vecCur, int2D vecPost);
    // MERGE SUPER!!!
    static Block1D mergeGlobal(Block1D oldVec, bool mergeRow = 0);
    // Rectangle Template
    static int2D rect(int2D vecSqr, int row, int col);

    // ================ File/Map Manipulation =================

    // Generate Block Code (.csv)
    static string0D blockToCode(Block *block);
    // Generate Block Info From Code
    static float2D codeToBlockInfo(string0D str);
    // Append Block To Map Based On File
    static void appendBlock(
        Map *map, string0D block_dir, short type = 0
    );
};
```

