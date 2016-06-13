angular.module("ConfiguratorApp", [ "ngMaterial", "Key", "Layouts" ])
	.config(function($mdThemingProvider) {
		$mdThemingProvider.theme('default')
			.primaryPalette('teal')
			.accentPalette('blue');
	})
	.controller("appCtrl", function($scope) {
		$scope.init_app = function() {
			document.onkeydown = function(e) {
				// broadcast keycode to every controller, and controller will do the map process to find the key
				event.preventDefault();
				console.log(e.code);
			}
		}
	})