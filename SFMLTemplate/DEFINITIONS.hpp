#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOW_TIME 3.0
#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_RATE 2.0f
#define BIRD_ANIMATION 0.4f
#define GRAVITY 45.0f
#define FLYING_SPEED 450.0f
#define FLYING_DURATION 0.25f
#define ROTATION_SPEED 200.0f
#define FLASH_SPEED 1500.0f
#define TIME_BEFORE_GO 1.5f

#define LAND_FILEPATH "Resources/res/Land.png"
#define SPLASH_SCREEN_BACKGROUND_PATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUNF_FILEPATH "Resources/res/sky.png"
#define GAME_BACKGROUNF_FILEPATH "Resources/res/sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/sky.png"
#define BIRD_FRAME_1_FILEPATH "Resources/res/bird-01.png"
#define BIRD_FRAME_2_FILEPATH "Resources/res/bird-02.png"
#define BIRD_FRAME_3_FILEPATH "Resources/res/bird-03.png"
#define BIRD_FRAME_4_FILEPATH "Resources/res/bird-04.png"

#define PIPE_UP_FILEPATH "Resources/res/PipeUp.png"
#define PIPE_DOWN_FILEPATH "Resources/res/PipeDown.png"

#define SCORING_PIPRE_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"

#define FLAPPY_FONT "Resources/fonts/FlappyFont.ttf"
#define GAME_OVER_FILEPATH "Resources/res/Game-Over-Title.png"
#define GAME_OVER__BODY_FILEPATH "Resources/res/Game-Over-Body.png"
#define HIGHSCORE_FILEPATH "Resources/highscore.txt"

enum GameStates {
	eReady,
	ePlaying,
	eGameover
};


