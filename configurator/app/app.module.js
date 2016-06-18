angular.module("ConfiguratorApp", [ "ngMaterial", "Key", "Layouts" ])
	.config(function($mdThemingProvider) {
		$mdThemingProvider.theme('default')
			.primaryPalette('teal')
			.accentPalette('blue');
	})
	.controller("appCtrl", function($scope, keyboardDataService) {
		$scope.init_app = function() {
			document.onkeydown = function(e) {
				event.preventDefault();
				$scope.$broadcast("keyPress", e.code);
			}

			$scope.loader = document.getElementById("loader");
			$scope.loader.addEventListener("change", $scope.load);
		}

		$scope.load = function() {
			var file = $scope.loader.files[0];
			if(!file) return;

			var reader = new FileReader();
			reader.onload = function(event) {
				var content = event.target.result;
				var configures = angular.fromJson(content);
				var custom_settings = keyboardDataService.get_custom_settings();

				for(var i = 0; i < custom_settings.length; ++i)
					custom_settings[i] = configures[i];

				console.log(custom_settings);
				$scope.$apply();
			}

			reader.readAsText(file);
		}

		$scope.output = function() {
			var ori_settings = keyboardDataService.get_ori_settings();
			var custom_settings = keyboardDataService.get_custom_settings();

			$scope.map_table = "uint8_t map_table[102] = { ";
			for(var i = 0; i <= 101; ++i) {
				if(ori_settings[i].hid_code == custom_settings[i].hid_code)
					$scope.map_table += " 0,";
				else
					$scope.map_table += " " + custom_settings[i].hid_code + ",";
			}
			$scope.map_table += " };";

			$scope.modifier_table = "uint8_t modifier_table[8] = {";
			for(var i = 102; i < 110; ++i) {
				if(ori_settings[i].hid_code == custom_settings[i].hid_code)
					$scope.modifier_table += " 0,";
				else
					$scope.modifier_table += " " + custom_settings[i].hid_code + ",";
			}
			$scope.modifier_table += " };";

			var content = "data:text/csv;charset=utf-8,";
			var link = document.createElement("a");
			link.setAttribute("download",  "keyboard_configure.dat");
			content += angular.toJson(custom_settings);
			var encodedUri = encodeURI(content);
			link.setAttribute("href", encodedUri);
			link.click();
		}

		$scope.press_load = function() {
			$scope.loader.click();
		}
	})