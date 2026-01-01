from pynput import keyboard

class KeyTracker:
    def __init__(self):
        self.a_pressed = False
        self.d_pressed = False

    def on_press(self, key):
        if key == keyboard.KeyCode.from_char('a'):
            self.a_pressed = True
        elif key == keyboard.KeyCode.from_char('d'):
            self.d_pressed = True

    def on_release(self, key):
        if key == keyboard.KeyCode.from_char('a'):
            self.a_pressed = False
        elif key == keyboard.KeyCode.from_char('d'):
            self.d_pressed = False


def create_tracker():
    tracker = KeyTracker()
    listener = keyboard.Listener(
        on_press=tracker.on_press,
        on_release=tracker.on_release
    )
    listener.start()
    return tracker
