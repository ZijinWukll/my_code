import pygame
import random
import sys
import math

# 初始化pygame
pygame.init()
pygame.mixer.init()  # 初始化音频

# 加载背景音乐
try:
    pygame.mixer.music.load("python/background.mp3")
    pygame.mixer.music.play(-1)  # 循环播放
except pygame.error:
    print("背景音乐文件未找到，跳过播放。")


# 获取屏幕分辨率并设置窗口高度为90%，宽度为原比例1.2倍
infoObject = pygame.display.Info()
SCREEN_WIDTH, SCREEN_HEIGHT = infoObject.current_w, infoObject.current_h
RATIO = 1400 / 900  # 原始宽高比
HEIGHT = int(SCREEN_HEIGHT * 0.9)
WIDTH = int(HEIGHT * RATIO * 1.2)
if WIDTH > int(SCREEN_WIDTH * 0.98):
    WIDTH = int(SCREEN_WIDTH * 0.98)
    HEIGHT = int(WIDTH / (RATIO * 1.2))
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("生日祝福游戏")

# 定义更多颜色（适合粉色背景）
COLORS = [
    (255, 0, 0),      # 红
    (255, 69, 0),     # 橙红
    (255, 165, 0),    # 橙
    (255, 255, 0),    # 黄
    (0, 255, 0),      # 绿
    (0, 255, 255),    # 青
    (0, 191, 255),    # 天蓝
    (138, 43, 226),   # 蓝紫
    (255, 0, 255),    # 品红
    (255, 20, 147),   # 深粉
    (255, 255, 255),  # 白
    (255, 215, 0),    # 金
    (255, 140, 0),    # 暗橙
    (0, 206, 209),    # 绿松石
    (255, 105, 180),  # 热粉
]

# 动态字体大小，基于窗口高度
font_scale = HEIGHT / 900
def get_font(name, size, bold=True):
    try:
        return pygame.font.SysFont(name, int(size * font_scale), bold=bold)
    except:
        return pygame.font.SysFont(None, int(size * font_scale), bold=bold)

font_large = get_font("microsoftyahei", 160)
font_medium = get_font("microsoftyahei", 110)
font_small = get_font("microsoftyahei", 60)
font_tiny = get_font("microsoftyahei", 40)

# 祝福语列表（扩展）
wishes = [
    "邓林杉生日快乐!",
    "祝dls生日快乐!",
    "祝邓林杉生日快乐!",
    "天天开心！",
    "学习进步！",
    "梦想成真！",
    "永远年轻，永远快乐！",
    "前程似锦！",
    "生日快乐！",
    "天天好运！"
    
    
    
]

# 动态背景类（固定粉色）
class DynamicBackground:
    def __init__(self):
        self.color = (255, 192, 203)  # 粉色

    def update(self):
        pass  # 不动

    def draw(self, screen):
        screen.fill(self.color)

# 飘落的祝福语类（增强）
class FallingWish:
    def __init__(self, text, x, y, speed, color, size, rotation_speed=0, scale_speed=0):
        self.text = text
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.rotation = 0
        self.rotation_speed = 0  # 不旋转
        self.scale = 1.0
        self.scale_speed = scale_speed
        # 动态字体，基于窗口缩放
        font_size = int(40 * self.size * font_scale)
        try:
            self.font = pygame.font.SysFont("microsoftyahei", font_size, bold=True)
        except:
            self.font = pygame.font.SysFont(None, font_size, bold=True)

    def update(self):
        self.y += self.speed
        self.rotation += self.rotation_speed
        self.scale += self.scale_speed
        if self.scale < 0.5 or self.scale > 2.0:
            self.scale_speed = -self.scale_speed
        if self.y > HEIGHT + 100:
            self.reset()

    def reset(self):
        self.y = random.randint(-HEIGHT, 0)
        self.x = random.randint(0, WIDTH - 200)
        self.rotation = 0
        self.scale = 1.0

    def draw(self, screen):
        text_surface = self.font.render(self.text, True, self.color)
        rotated_surface = pygame.transform.rotate(text_surface, self.rotation)
        scaled_surface = pygame.transform.scale(rotated_surface, (int(rotated_surface.get_width() * self.scale), int(rotated_surface.get_height() * self.scale)))
        screen.blit(scaled_surface, (self.x - scaled_surface.get_width() // 2, self.y - scaled_surface.get_height() // 2))

# 五角星类
class Star:
    def __init__(self, x, y, speed, color, size):
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.rotation = 0
        self.rotation_speed = 0  # 不旋转

    def update(self):
        self.y += self.speed
        self.rotation += self.rotation_speed
        if self.y > HEIGHT + 50:
            self.y = -50
            self.x = random.randint(0, WIDTH)

    def draw(self, screen):
        points = []
        for i in range(5):
            angle = math.radians(i * 72 - 90)
            x = self.x + self.size * math.cos(angle)
            y = self.y + self.size * math.sin(angle)
            points.append((x, y))
            angle = math.radians(i * 72 + 36 - 90)
            x = self.x + self.size * 0.5 * math.cos(angle)
            y = self.y + self.size * 0.5 * math.sin(angle)
            points.append((x, y))
        rotated_points = []
        for px, py in points:
            dx = px - self.x
            dy = py - self.y
            cos_r = math.cos(math.radians(self.rotation))
            sin_r = math.sin(math.radians(self.rotation))
            rx = dx * cos_r - dy * sin_r + self.x
            ry = dx * sin_r + dy * cos_r + self.y
            rotated_points.append((rx, ry))
        pygame.draw.polygon(screen, self.color, rotated_points)

# 雪花类
class Snowflake:
    def __init__(self, x, y, speed, color, size):
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.rotation = 0
        self.rotation_speed = 0  # 不旋转

    def update(self):
        self.y += self.speed
        self.x += random.uniform(-0.5, 0.5)
        self.rotation += self.rotation_speed
        if self.y > HEIGHT + 50:
            self.y = -50
            self.x = random.randint(0, WIDTH)

    def draw(self, screen):
        # 简单雪花形状
        pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.size)
        for i in range(6):
            angle = math.radians(i * 60)
            end_x = self.x + self.size * 2 * math.cos(angle)
            end_y = self.y + self.size * 2 * math.sin(angle)
            pygame.draw.line(screen, self.color, (self.x, self.y), (end_x, end_y), 2)

# 生日蛋糕类（使用图片或图形）
class Cake:
    def __init__(self, x, y, speed, color, size):
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.scale = 1.0
        self.scale_speed = random.uniform(0.003, 0.012)
        try:
            self.image = pygame.image.load("python/cake1.png").convert_alpha()
            self.use_image = True
        except FileNotFoundError:
            self.use_image = False

    def update(self):
        self.y += self.speed
        self.scale += self.scale_speed
        if self.scale > 1.30 or self.scale < 0.85:
            self.scale_speed = -self.scale_speed
        if self.y > HEIGHT + 100:
            self.y = -100
            self.x = random.randint(0, WIDTH - 100)

    def draw(self, screen):
        base = HEIGHT / 900  # 元素基准缩放
        if self.use_image:
            scaled_image = pygame.transform.scale(
                self.image,
                (int(self.image.get_width() * self.scale * self.size * 0.27 * base),
                 int(self.image.get_height() * self.scale * self.size * 0.27 * base))
            )
            screen.blit(scaled_image, (self.x, self.y))
        else:
            width = int(100 * self.scale * self.size * base)
            height = int(60 * self.scale * self.size * base)
            pygame.draw.rect(screen, self.color, (self.x, self.y, width, height))
            pygame.draw.rect(screen, (255, 255, 255), (self.x, self.y - 20 * self.scale * self.size * base, width, 20 * self.scale * self.size * base))

# 圣诞树类（使用图片或图形）
class ChristmasTree:
    def __init__(self, x, y, speed, color, size, only23=False):
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.rotation = 0
        self.rotation_speed = 0  # 不旋转
        # 只从tree2和tree3中选
        if only23:
            tree_choices = ["tree2.png", "tree3.png"]
        else:
            tree_choices = ["tree2.png", "tree3.png"]  # tree1不再参与下落动画
        self.tree_name = random.choice(tree_choices)
        try:
            self.image = pygame.image.load(f"python/{self.tree_name}").convert_alpha()
            self.use_image = True
        except FileNotFoundError:
            self.use_image = False

    def update(self):
        self.y += self.speed
        self.rotation += self.rotation_speed
        if self.y > HEIGHT + 200:
            self.y = -200
            self.x = random.randint(0, WIDTH - 100)

    def draw(self, screen):
        base = HEIGHT / 900
        if self.use_image:
            # tree3缩小3倍
            if hasattr(self, "tree_name") and self.tree_name == "tree3.png":
                scale_factor = (0.16 / 3) * base
                x_stretch = 1.0
            else:
                scale_factor = 0.16 * base
                x_stretch = 1.0
            rotated_image = pygame.transform.rotate(self.image, self.rotation)
            scaled_image = pygame.transform.scale(
                rotated_image,
                (int(rotated_image.get_width() * self.size * scale_factor * x_stretch),
                 int(rotated_image.get_height() * self.size * scale_factor))
            )
            screen.blit(scaled_image, (self.x, self.y))
        else:
            # 简单树形
            points = [
                (self.x, self.y + 100 * self.size * base),
                (self.x - 50 * self.size * base, self.y + 100 * self.size * base),
                (self.x - 25 * self.size * base, self.y + 50 * self.size * base),
                (self.x - 50 * self.size * base, self.y + 50 * self.size * base),
                (self.x, self.y),
                (self.x + 50 * self.size * base, self.y + 50 * self.size * base),
                (self.x + 25 * self.size * base, self.y + 50 * self.size * base),
                (self.x + 50 * self.size * base, self.y + 100 * self.size * base),
            ]
            pygame.draw.polygon(screen, self.color, points)


# 初始化对象
background = DynamicBackground()
falling_wishes = []
stars = []
snowflakes = []
cakes = []
trees = []

# 固定顶部tree1图片
try:
    tree1_image = pygame.image.load("python/tree1.png").convert_alpha()
    tree1_show = True
except FileNotFoundError:
    tree1_show = False

# 创建祝福语
for i in range(10):
    wish = random.choice(wishes)
    x = random.randint(0, WIDTH - 200)
    y = random.randint(-HEIGHT, 0)
    speed = random.uniform(1, 4)
    available_colors = [c for c in COLORS if c != (255, 192, 203)]
    color = random.choice(available_colors)
    size = random.uniform(0.8, 2.0)
    rotation_speed = 0  # 不旋转
    scale_speed = random.uniform(-0.01, 0.01)
    falling_wishes.append(FallingWish(wish, x, y, speed, color, size, rotation_speed, scale_speed))

# 创建其他元素
for i in range(10):
    x = random.randint(0, WIDTH)
    y = random.randint(-HEIGHT, 0)
    speed = random.uniform(1, 3)
    color = random.choice(COLORS)
    size = random.randint(5, 15)
    stars.append(Star(x, y, speed, color, size))

for i in range(10):
    x = random.randint(0, WIDTH)
    y = random.randint(-HEIGHT, 0)
    speed = random.uniform(0.5, 2)
    color = (255, 255, 255)
    size = random.randint(3, 8)
    snowflakes.append(Snowflake(x, y, speed, color, size))

for i in range(5):
    x = random.randint(0, WIDTH - 100)
    y = random.randint(-HEIGHT, 0)
    speed = random.uniform(0.5, 2)
    color = random.choice(COLORS)
    size = random.uniform(0.8, 1.5)
    cakes.append(Cake(x, y, speed, color, size))

for i in range(5):
    x = random.randint(0, WIDTH - 100)
    y = random.randint(-HEIGHT, 0)
    speed = random.uniform(1.2, 3.5)  # 下落速度增快
    color = (0, 128, 0)
    size = random.uniform(0.8, 1.5)
    trees.append(ChristmasTree(x, y, speed, color, size))

# 主循环
running = True
show_main_wish = True
main_wish_index = 0
main_color_timer = 0
main_color = random.choice(COLORS)
clock = pygame.time.Clock()


while running:
    background.update()
    background.draw(screen)

    # 固定tree1图片最顶端居中
    if tree1_show:
        base = HEIGHT / 900
        scale_factor = 1.0 * base
        x_stretch = 2.0  # 横向拉伸2倍
        img = pygame.transform.scale(
            tree1_image,
            (int(tree1_image.get_width() * scale_factor * x_stretch),
             int(tree1_image.get_height() * scale_factor))
        )
        x_pos = WIDTH // 2 - img.get_width() // 2
        y_pos = 0
        screen.blit(img, (x_pos, y_pos))

    # 更新和绘制元素
    for wish in falling_wishes:
        wish.update()
        wish.draw(screen)

    for star in stars:
        star.update()
        star.draw(screen)

    for snowflake in snowflakes:
        snowflake.update()
        snowflake.draw(screen)

    for cake in cakes:
        cake.update()
        cake.draw(screen)

    for tree in trees:
        tree.update()
        tree.draw(screen)

    # 更新主祝福语颜色
    main_color_timer += 1
    if main_color_timer > 120:  # 每120帧换色，约2秒
        main_color_timer = 0
        available_colors = [c for c in COLORS if c != (255, 192, 203)]  # 排除粉色
        main_color = random.choice(available_colors)

    # 更新和绘制元素
    for wish in falling_wishes:
        wish.update()
        wish.draw(screen)

    for star in stars:
        star.update()
        star.draw(screen)

    for snowflake in snowflakes:
        snowflake.update()
        snowflake.draw(screen)

    for cake in cakes:
        cake.update()
        cake.draw(screen)

    for tree in trees:
        tree.update()
        tree.draw(screen)

    # 显示主祝福语
    if show_main_wish:
        main_text = font_large.render(wishes[main_wish_index], True, main_color)
        screen.blit(main_text, (WIDTH // 2 - main_text.get_width() // 2, HEIGHT // 2 - main_text.get_height() // 2))

    # 事件处理
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            main_wish_index = (main_wish_index + 1) % len(wishes)
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                show_main_wish = not show_main_wish
            elif event.key == pygame.K_ESCAPE:
                running = False

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
sys.exit()