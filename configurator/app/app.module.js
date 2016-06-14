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
		}

		$scope.output = function() {
			var ori_settings = keyboardDataService.get_ori_settings();
			var custom_settings = keyboardDataService.get_custom_settings();

			var map_table = "uint8_t map_table[102] = { ";
			for(var i = 0; i <= 101; ++i) {
				if(ori_settings[i].hid_code == custom_settings[i].hid_code)
					map_table += " 0,";
				else
					map_table += " " + custom_settings[i].hid_code + ",";
			}
			map_table += " };";

			var modifier_table = "uint8_t modifier_table[8] = {";
			for(var i = 102; i < 110; ++i) {
				if(ori_settings[i].hid_code == custom_settings[i].hid_code)
					modifier_table += " 0,";
				else
					modifier_table += " " + custom_settings[i].hid_code + ",";
			}
			modifier_table += " };";
		}
	})