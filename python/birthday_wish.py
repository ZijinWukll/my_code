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

# 设置窗口大小（较大界面框）
WIDTH, HEIGHT = 1400, 900
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

# 字体（使用系统中文字体，更粗）
try:
    font_large = pygame.font.SysFont("microsoftyahei", 180, bold=True)  # 微软雅黑，更大更粗
    font_medium = pygame.font.SysFont("microsoftyahei", 100, bold=True)
    font_small = pygame.font.SysFont("microsoftyahei", 60, bold=True)
    font_tiny = pygame.font.SysFont("microsoftyahei", 40, bold=True)
except:
    try:
        font_large = pygame.font.SysFont("simsun", 180, bold=True)  # 宋体
        font_medium = pygame.font.SysFont("simsun", 100, bold=True)
        font_small = pygame.font.SysFont("simsun", 60, bold=True)
        font_tiny = pygame.font.SysFont("simsun", 40, bold=True)
    except:
        font_large = pygame.font.SysFont(None, 180, bold=True)
        font_medium = pygame.font.SysFont(None, 100, bold=True)
        font_small = pygame.font.SysFont(None, 60, bold=True)
        font_tiny = pygame.font.SysFont(None, 40, bold=True)

# 祝福语列表（扩展）
wishes = [
    "生日快乐!",
    "祝你生日快乐！",
    "生日快乐！",
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
        try:
            self.font = pygame.font.SysFont("microsoftyahei", int(40 * self.size), bold=True)
        except:
            try:
                self.font = pygame.font.SysFont("simsun", int(40 * self.size), bold=True)
            except:
                self.font = pygame.font.SysFont(None, int(40 * self.size), bold=True)

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
        self.scale_speed = random.uniform(0.01, 0.05)
        try:
            self.image = pygame.image.load("python/cake1.png").convert_alpha()
            self.use_image = True
        except FileNotFoundError:
            self.use_image = False

    def update(self):
        self.y += self.speed
        self.scale += self.scale_speed
        if self.scale > 1.5 or self.scale < 0.8:
            self.scale_speed = -self.scale_speed
        if self.y > HEIGHT + 100:
            self.y = -100
            self.x = random.randint(0, WIDTH - 100)

    def draw(self, screen):
        if self.use_image:
            scaled_image = pygame.transform.scale(self.image, (int(self.image.get_width() * self.scale * self.size * 0.27), int(self.image.get_height() * self.scale * self.size * 0.27)))
            screen.blit(scaled_image, (self.x, self.y))
        else:
            # 简单蛋糕形状
            width = int(100 * self.scale * self.size)
            height = int(60 * self.scale * self.size)
            pygame.draw.rect(screen, self.color, (self.x, self.y, width, height))
            pygame.draw.rect(screen, (255, 255, 255), (self.x, self.y - 20 * self.scale * self.size, width, 20 * self.scale * self.size))  # 奶油

# 圣诞树类（使用图片或图形）
class ChristmasTree:
    def __init__(self, x, y, speed, color, size):
        self.x = x
        self.y = y
        self.speed = speed
        self.color = color
        self.size = size
        self.rotation = 0
        self.rotation_speed = 0  # 不旋转
        try:
            self.image = pygame.image.load("python/" + random.choice(["tree1.png", "tree2.png"])).convert_alpha()
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
        if self.use_image:
            rotated_image = pygame.transform.rotate(self.image, self.rotation)
            scaled_image = pygame.transform.scale(rotated_image, (int(rotated_image.get_width() * self.size * 0.16), int(rotated_image.get_height() * self.size * 0.16)))
            screen.blit(scaled_image, (self.x, self.y))
        else:
            # 简单树形
            points = [
                (self.x, self.y + 100 * self.size),
                (self.x - 50 * self.size, self.y + 100 * self.size),
                (self.x - 25 * self.size, self.y + 50 * self.size),
                (self.x - 50 * self.size, self.y + 50 * self.size),
                (self.x, self.y),
                (self.x + 50 * self.size, self.y + 50 * self.size),
                (self.x + 25 * self.size, self.y + 50 * self.size),
                (self.x + 50 * self.size, self.y + 100 * self.size),
            ]
            pygame.draw.polygon(screen, self.color, points)

# 初始化对象
background = DynamicBackground()
falling_wishes = []
stars = []
snowflakes = []
cakes = []
trees = []

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
    speed = random.uniform(0.5, 2)
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