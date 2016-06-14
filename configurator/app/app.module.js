angular.module("ConfiguratorApp", [ "ngMaterial", "Key", "Layouts" ])
	.config(function($mdThemingProvider) {
		$mdThemingProvider.theme('default')
			.primaryPalette('teal')
			.accentPalette('blue');
	})
	.controller("appCtrl", function($scope) {
		$scope.init_app = function() {
			document.onkeydown = function(e) {
				event.preventDefault();
				$scope.$broadcast("keyPress", e.code);
			}
		}
	})