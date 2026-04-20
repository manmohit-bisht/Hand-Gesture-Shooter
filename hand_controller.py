import cv2
import mediapipe as mp
import pyautogui
import numpy as np
import time


mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.5
)

# Initialize camera
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

shoot_cooldown = 0
current_action = "STOP"  
space_pressed = False  

# Center zone settings
FRAME_WIDTH = 640
CENTER_ZONE_WIDTH = 150  # Width of center "dead zone"
LEFT_ZONE = FRAME_WIDTH // 2 - CENTER_ZONE_WIDTH // 2
RIGHT_ZONE = FRAME_WIDTH // 2 + CENTER_ZONE_WIDTH // 2

print("Hand Gesture Controller Started!")
print("Controls:")
print("- Left zone: Move spaceship left")
print("- Center zone: Stay in place") 
print("- Right zone: Move spaceship right")
print("- Make a fist to shoot")
print("- Press 'q' to quit")

while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    shoot_cooldown = max(0, shoot_cooldown - 1)
    
    frame = cv2.flip(frame, 1)
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    cv2.line(frame, (LEFT_ZONE, 0), (LEFT_ZONE, 480), (0, 255, 255), 2) 
    cv2.line(frame, (RIGHT_ZONE, 0), (RIGHT_ZONE, 480), (0, 255, 255), 2)  
    
    # Draw zone labels
    cv2.putText(frame, "LEFT", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.putText(frame, "CENTER", (LEFT_ZONE + 50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 255), 2)
    cv2.putText(frame, "RIGHT", (RIGHT_ZONE + 50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    
    results = hands.process(rgb_frame)
    
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            
            wrist = hand_landmarks.landmark[mp_hands.HandLandmark.WRIST]
            hand_x = wrist.x * FRAME_WIDTH
            
            
            new_action = "STOP"
            if hand_x < LEFT_ZONE:

                new_action = "LEFT"
                if current_action != "LEFT":
                    pyautogui.keyUp('d') 
                    pyautogui.keyDown('a') 
                    current_action = "LEFT"
            elif hand_x > RIGHT_ZONE:
        
                new_action = "RIGHT"
                if current_action != "RIGHT":
                    pyautogui.keyUp('a') 
                    pyautogui.keyDown('d')  
                    current_action = "RIGHT"
            else:
                
                new_action = "STOP"
                if current_action != "STOP":
                    pyautogui.keyUp('a')  
                    pyautogui.keyUp('d')  
                    current_action = "STOP"

            cv2.putText(frame, f"Action: {current_action}", (10, 400), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
            
            hand_center = (int(hand_x), int(wrist.y * 480))
            cv2.circle(frame, hand_center, 10, (255, 0, 0), -1)
            
            thumb_tip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]
            thumb_ip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_IP]
            index_tip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]
            index_pip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_PIP]
            middle_tip = hand_landmarks.landmark[mp_hands.HandLandmark.MIDDLE_FINGER_TIP]
            middle_pip = hand_landmarks.landmark[mp_hands.HandLandmark.MIDDLE_FINGER_PIP]
            ring_tip = hand_landmarks.landmark[mp_hands.HandLandmark.RING_FINGER_TIP]
            ring_pip = hand_landmarks.landmark[mp_hands.HandLandmark.RING_FINGER_PIP]
            
            fingers_down = 0
            if thumb_tip.y > thumb_ip.y:
                fingers_down += 1
            if index_tip.y > index_pip.y:
                fingers_down += 1
            if middle_tip.y > middle_pip.y:
                fingers_down += 1
            if ring_tip.y > ring_pip.y:
                fingers_down += 1
            
            
            if fingers_down >= 3 and shoot_cooldown == 0:
                print("SHOOTING!")
                if not space_pressed:
                    pyautogui.keyDown('space')
                    space_pressed = True
                shoot_cooldown = 30
                cv2.putText(frame, "SHOOT!", (10, 350), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 3)
            else:
                
                if space_pressed:
                    pyautogui.keyUp('space')
                    space_pressed = False
            
            cv2.putText(frame, f"Fingers down: {fingers_down}", (10, 320), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 0), 2)
    
    else:
        
        if current_action != "STOP":
            pyautogui.keyUp('a')
            pyautogui.keyUp('d')
            current_action = "STOP"
        if space_pressed:
            pyautogui.keyUp('space')
            space_pressed = False
        cv2.putText(frame, "No hand detected", (10, 400), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    
    cv2.putText(frame, "Move hand to left/center/right zones", (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
    cv2.putText(frame, "Make fist to shoot | Press 'q' to quit", (10, 470), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
    
    cv2.imshow('Hand Gesture Controller', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Cleanup
pyautogui.keyUp('a')
pyautogui.keyUp('d')
if space_pressed:
    pyautogui.keyUp('space')
cap.release()
cv2.destroyAllWindows()