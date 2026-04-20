#include "spaceship.hpp"

int main()
{
    InitWindow(1080, 720, "Space Shooter");
    SetWindowState(FLAG_VSYNC_HINT);

    Ship ship(500, KEY_A, KEY_D, KEY_SPACE);
    ship.loadTextures();
    
    // Load textures
    Texture2D enemyTexture = LoadTexture("assets/PNG/Enemies/enemyRed1.png");
    Texture2D playerBulletTexture = LoadTexture("assets/PNG/Lasers/laserBlue01.png");
    Texture2D enemyBulletTexture = LoadTexture("assets/PNG/Lasers/laserRed01.png");
    
    // Game objects
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    
    float enemySpawnTimer = 0;
    bool gameOver = false;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        if (!gameOver) {
            // Update ship
            ship.update();
            
            // Player shooting
            if (ship.canShoot()) {
                bullets.push_back(Bullet({ship.position.x + ship.texture.width/2, ship.position.y}, {0, -400}, true));
                ship.shoot();
            }
            
            // Spawn enemies
            enemySpawnTimer += dt;
            if (enemySpawnTimer > 1.5f) {
                float x = GetRandomValue(0, 1080 - enemyTexture.width);
                enemies.push_back(Enemy({x, -50}));
                enemySpawnTimer = 0;
            }
            
            // Update enemies
            for (auto& enemy : enemies) {
                if (enemy.active) {
                    enemy.update();
                    
                    // Enemy shooting
                    if (enemy.shouldShoot()) {
                        bullets.push_back(Bullet({enemy.position.x + enemyTexture.width/2, enemy.position.y + enemyTexture.height}, {0, 200}, false));
                        enemy.resetShootTimer();
                    }
                }
            }
            
            // Update bullets
            for (auto& bullet : bullets) {
                if (bullet.active) {
                    bullet.update();
                }
            }
            
            // Collision detection
            Rectangle shipRect = ship.getBounds();
            
            // Check bullet-enemy collisions
            for (auto& bullet : bullets) {
                if (bullet.active && bullet.isPlayerBullet) {
                    Rectangle bulletRect = {bullet.position.x, bullet.position.y, (float)playerBulletTexture.width, (float)playerBulletTexture.height};
                    
                    for (auto& enemy : enemies) {
                        if (enemy.active) {
                            Rectangle enemyRect = {enemy.position.x, enemy.position.y, (float)enemyTexture.width, (float)enemyTexture.height};
                            
                            if (CheckCollisionRecs(bulletRect, enemyRect)) {
                                bullet.active = false;
                                enemy.active = false;
                            }
                        }
                    }
                }
            }
            
            // Check enemy bullet-player collisions
            for (auto& bullet : bullets) {
                if (bullet.active && !bullet.isPlayerBullet) {
                    Rectangle bulletRect = {bullet.position.x, bullet.position.y, (float)enemyBulletTexture.width, (float)enemyBulletTexture.height};
                    
                    if (CheckCollisionRecs(bulletRect, shipRect)) {
                        bullet.active = false;
                        hp--;
                        if (hp <= 0) {
                            gameOver = true;
                        }
                    }
                }
            }
            
            // Check enemy-player collisions
            for (auto& enemy : enemies) {
                if (enemy.active) {
                    Rectangle enemyRect = {enemy.position.x, enemy.position.y, (float)enemyTexture.width, (float)enemyTexture.height};
                    
                    if (CheckCollisionRecs(enemyRect, shipRect)) {
                        enemy.active = false;
                        hp--;
                        if (hp <= 0) {
                            gameOver = true;
                        }
                    }
                }
            }
            
            // Remove inactive objects
            enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.active; }), enemies.end());
            bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.active; }), bullets.end());
        }
        
        // Restart game
        if (gameOver && IsKeyPressed(KEY_R)) {
            hp = 7;
            gameOver = false;
            enemies.clear();
            bullets.clear();
            ship.position = {500, 600};
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        
        if (!gameOver) {
            // Draw ship
            DrawTexture(ship.texture, (int)ship.position.x, (int)ship.position.y, WHITE);
            
            // Draw enemies
            for (const auto& enemy : enemies) {
                if (enemy.active) {
                    DrawTexture(enemyTexture, (int)enemy.position.x, (int)enemy.position.y, WHITE);
                }
            }
            
            // Draw bullets
            for (const auto& bullet : bullets) {
                if (bullet.active) {
                    if (bullet.isPlayerBullet) {
                        DrawTexture(playerBulletTexture, (int)bullet.position.x, (int)bullet.position.y, WHITE);
                    } else {
                        DrawTexture(enemyBulletTexture, (int)bullet.position.x, (int)bullet.position.y, WHITE);
                    }
                }
            }
            
            // Draw HP
            DrawText(TextFormat("HP: %d", hp), 10, 10, 30, WHITE);
        } else {
            // Game over screen
            DrawText("GAME OVER", 400, 300, 60, RED);
            DrawText("Press R to restart", 420, 380, 30, WHITE);
        }

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(ship.texture);
    UnloadTexture(enemyTexture);
    UnloadTexture(playerBulletTexture);
    UnloadTexture(enemyBulletTexture);
    CloseWindow();
    
    return 0;
}
