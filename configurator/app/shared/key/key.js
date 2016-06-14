angular.module("Key", ["ngMaterial"])
	.directive("key", function() {
		return {
			restrict: "E",
			scope: {
				keyObj: "="
			},
			templateUrl: "app/shared/key/key.html",
			controller: function($scope, keyboardDataService) {
				$scope.init_key = function() {
					$scope.selected = false;
				}

				$scope.click_key = function() {
					if (!$scope.selected)
						$scope.$emit("selectEvnt", $scope.keyObj);
					$scope.selected = !$scope.selected;
				}

				$scope.$on("keyPress", function(e, code) {
					if ($scope.selected) {
						$scope.keyObj = keyboardDataService.transform_to_input_code(code);
						$scope.$apply();
					}
				});

				$scope.$on("unselect", function(e) {
					$scope.selected = false;
				});

				$scope.$on("setConsumerKey", function(e, keyObj) {
					if ($scope.selected) {
						$scope.keyObj = keyObj;
						$scope.$apply();
					}
				});
			}
		}
	})
	.service("keyboardDataService", function() {
		var KeyDaturm = function(representation, hid_code, is_modifier) {
			this.representation = representation;
			this.hid_code = hid_code;
			this.is_modifier = is_modifier;
		}

		var key_data = {
			"None": new KeyDaturm(" ", 0, false),
			"KeyA": new KeyDaturm("A", 4, false),
			"KeyB": new KeyDaturm("B", 5, false),
			"KeyC": new KeyDaturm("C", 6, false),
			"KeyD": new KeyDaturm("D", 7, false),
			"KeyE": new KeyDaturm("E", 8, false),
			"KeyF": new KeyDaturm("F", 9, false),
			"KeyG": new KeyDaturm("G", 10, false),
			"KeyH": new KeyDaturm("H", 11, false),
			"KeyI": new KeyDaturm("I", 12, false),
			"KeyJ": new KeyDaturm("J", 13, false),
			"KeyK": new KeyDaturm("K", 14, false),
			"KeyL": new KeyDaturm("L", 15, false),
			"KeyM": new KeyDaturm("M", 16, false),
			"KeyN": new KeyDaturm("N", 17, false),
			"KeyO": new KeyDaturm("O", 18, false),
			"KeyP": new KeyDaturm("P", 19, false),
			"KeyQ": new KeyDaturm("Q", 20, false),
			"KeyR": new KeyDaturm("R", 21, false),
			"KeyS": new KeyDaturm("S", 22, false),
			"KeyT": new KeyDaturm("T", 23, false),
			"KeyU": new KeyDaturm("U", 24, false),
			"KeyV": new KeyDaturm("V", 25, false),
			"KeyW": new KeyDaturm("W", 26, false),
			"KeyX": new KeyDaturm("X", 27, false),
			"KeyY": new KeyDaturm("Y", 28, false),
			"KeyZ": new KeyDaturm("Z", 29, false),
			"Digit1": new KeyDaturm("1", 30, false),
			"Digit2": new KeyDaturm("2", 31, false),
			"Digit3": new KeyDaturm("3", 32, false),
			"Digit4": new KeyDaturm("4", 33, false),
			"Digit5": new KeyDaturm("5", 34, false),
			"Digit6": new KeyDaturm("6", 35, false),
			"Digit7": new KeyDaturm("7", 36, false),
			"Digit8": new KeyDaturm("8", 37, false),
			"Digit9": new KeyDaturm("9", 38, false),
			"Digit0": new KeyDaturm("0", 39, false),
			"Enter": new KeyDaturm("Enter", 40, false),
			"Escape": new KeyDaturm("Esc", 41, false),
			"Backspace": new KeyDaturm("⌫", 42, false),
			"Tab": new KeyDaturm("Tab", 43, false),
			"Space": new KeyDaturm("Space", 44, false),
			"Minus": new KeyDaturm("-", 45, false),
			"Equal": new KeyDaturm("=", 46, false),
			"BracketLeft": new KeyDaturm("{", 47, false),
			"BracketRight": new KeyDaturm("}", 48, false),
			"Backslash": new KeyDaturm("\\", 49, false),
			"Semicolon": new KeyDaturm(";", 51, false),
			"Quote": new KeyDaturm("\'", 52, false),
			"Backquote": new KeyDaturm("`", 53, false),
			"Comma": new KeyDaturm(",", 54, false),
			"Period": new KeyDaturm(".", 55, false),
			"Slash": new KeyDaturm("/", 56, false),
			"CapsLock": new KeyDaturm("CapsLock", 57, false),
			"F1": new KeyDaturm("F1", 58, false),
			"F2": new KeyDaturm("F2", 59, false),
			"F3": new KeyDaturm("F3", 60, false),
			"F4": new KeyDaturm("F4", 61, false),
			"F5": new KeyDaturm("F5", 62, false),
			"F6": new KeyDaturm("F6", 63, false),
			"F7": new KeyDaturm("F7", 64, false),
			"F8": new KeyDaturm("F8", 65, false),
			"F9": new KeyDaturm("F9", 66, false),
			"F10": new KeyDaturm("F10", 67, false),
			"F11": new KeyDaturm("F11", 68, false),
			"F12": new KeyDaturm("F12", 69, false),
			"F13": new KeyDaturm("F13", 70, false),
			"PrintScreen": new KeyDaturm("PrtScn", 70, false),
			"F14": new KeyDaturm("F14", 71, false),
			"ScrollLock": new KeyDaturm("ScrLk", 71, false),
			"F15": new KeyDaturm("F15", 72, false),
			"Pause": new KeyDaturm("Pause", 72, false),
			"Insert": new KeyDaturm("Insert", 73, false),
			"Home": new KeyDaturm("Home", 74, false),
			"PageUp": new KeyDaturm("PageUp", 75, false),
			"Delete": new KeyDaturm("Del", 76, false),
			"End": new KeyDaturm("End", 77, false),
			"PageDown": new KeyDaturm("PageDown", 78, false),
			"ArrowRight": new KeyDaturm("→", 79, false),
			"ArrowLeft": new KeyDaturm("←", 80, false),
			"ArrowDown": new KeyDaturm("↓", 81, false),
			"ArrowUp": new KeyDaturm("↑", 82, false),
			"NumLock": new KeyDaturm("NumLock", 83, false),
			"NumpadDivide": new KeyDaturm("/", 84, false),
			"NumpadMultiply": new KeyDaturm("*", 85, false),
			"NumpadSubtract": new KeyDaturm("-", 86, false),
			"NumpadAdd": new KeyDaturm("+", 87, false),
			"NumpadEnter": new KeyDaturm("Enter", 88, false),
			"Numpad1": new KeyDaturm("1", 89, false),
			"Numpad2": new KeyDaturm("2", 90, false),
			"Numpad3": new KeyDaturm("3", 91, false),
			"Numpad4": new KeyDaturm("4", 92, false),
			"Numpad5": new KeyDaturm("5", 93, false),
			"Numpad6": new KeyDaturm("6", 94, false),
			"Numpad7": new KeyDaturm("7", 95, false),
			"Numpad8": new KeyDaturm("8", 96, false),
			"Numpad9": new KeyDaturm("9", 97, false),
			"Numpad0": new KeyDaturm("0", 98, false),
			"NumpadDecimal": new KeyDaturm(".", 99, false),
			"ContextMenu": new KeyDaturm("menu", 101, false),
			"VolumeUp": new KeyDaturm("🔈+", 128, false),
			"VolumeDown": new KeyDaturm("🔈-", 129, false),
			"ConsumerHome": new KeyDaturm("🏠", 130, false),
			"Search": new KeyDaturm("🔍", 131, false),
			"Play/Pause": new KeyDaturm("⏯", 132, false),
			"Stop": new KeyDaturm("⏹", 133, false),
			"ControlLeft": new KeyDaturm("L-Ctrl", 224, true),
			"ShiftLeft": new KeyDaturm("L-Shift", 225, true),
			"AltLeft": new KeyDaturm("L-Alt", 226, true),
			"OSLeft": new KeyDaturm("L-⌘", 227, true),
			"ControlRight": new KeyDaturm("R-Ctrl", 228, true),
			"ShiftRight": new KeyDaturm("R-Shift", 229, true),
			"AltRight": new KeyDaturm("R-Alt", 230, true),
			"OSRight": new KeyDaturm("R-⌘", 231, true),
		};

		var custom_settings = [
			key_data["None"],
			key_data["None"],
			key_data["None"],
			key_data["None"],
			key_data["KeyA"],
			key_data["KeyB"],
			key_data["KeyC"],
			key_data["KeyD"],
			key_data["KeyE"],
			key_data["KeyF"],
			key_data["KeyG"],
			key_data["KeyH"],
			key_data["KeyI"],
			key_data["KeyJ"],
			key_data["KeyK"],
			key_data["KeyL"],
			key_data["KeyM"],
			key_data["KeyN"],
			key_data["KeyO"],
			key_data["KeyP"],
			key_data["KeyQ"],
			key_data["KeyR"],
			key_data["KeyS"],
			key_data["KeyT"],
			key_data["KeyU"],
			key_data["KeyV"],
			key_data["KeyW"],
			key_data["KeyX"],
			key_data["KeyY"],
			key_data["KeyZ"],
			key_data["Digit1"],
			key_data["Digit2"],
			key_data["Digit3"],
			key_data["Digit4"],
			key_data["Digit5"],
			key_data["Digit6"],
			key_data["Digit7"],
			key_data["Digit8"],
			key_data["Digit9"],
			key_data["Digit0"],
			key_data["Enter"],
			key_data["Escape"],
			key_data["Backspace"],
			key_data["Tab"],
			key_data["Space"],
			key_data["Minus"],
			key_data["Equal"],
			key_data["BracketLeft"],
			key_data["BracketRight"],
			key_data["Backslash"],
			key_data["None"],
			key_data["Semicolon"],
			key_data["Quote"],
			key_data["Backquote"],
			key_data["Comma"],
			key_data["Period"],
			key_data["Slash"],
			key_data["CapsLock"],
			key_data["F1"],
			key_data["F2"],
			key_data["F3"],
			key_data["F4"],
			key_data["F5"],
			key_data["F6"],
			key_data["F7"],
			key_data["F8"],
			key_data["F9"],
			key_data["F10"],
			key_data["F11"],
			key_data["F12"],
			key_data["PrintScreen"],
			key_data["ScrollLock"],
			key_data["Pause"],
			key_data["Insert"],
			key_data["Home"],
			key_data["PageUp"],
			key_data["Delete"],
			key_data["End"],
			key_data["PageDown"],
			key_data["ArrowRight"],
			key_data["ArrowLeft"],
			key_data["ArrowDown"],
			key_data["ArrowUp"],
			key_data["NumLock"],
			key_data["NumpadDivide"],
			key_data["NumpadMultiply"],
			key_data["NumpadSubtract"],
			key_data["NumpadAdd"],
			key_data["NumpadEnter"],
			key_data["Numpad1"],
			key_data["Numpad2"],
			key_data["Numpad3"],
			key_data["Numpad4"],
			key_data["Numpad5"],
			key_data["Numpad6"],
			key_data["Numpad7"],
			key_data["Numpad8"],
			key_data["Numpad9"],
			key_data["Numpad0"],
			key_data["NumpadDecimal"],
			key_data["None"],
			key_data["ContextMenu"],
			key_data["ControlLeft"],
			key_data["ShiftLeft"],
			key_data["AltLeft"],
			key_data["OSLeft"],
			key_data["ControlRight"],
			key_data["ShiftRight"],
			key_data["AltRight"],
			key_data["OSRight"],
		];

		var consumer_data = [
			key_data["VolumeUp"],
			key_data["VolumeDown"],
			key_data["ConsumerHome"],
			key_data["Search"],
			key_data["Play/Pause"],
			key_data["Stop"]
		];

		return {
			transform_to_input_code: function(keycode) {
				return key_data[keycode]; },
			get_custom_settings: function() {
				return custom_settings; },
			get_consumer_data: function() {
				return consumer_data; },
		}
	})
