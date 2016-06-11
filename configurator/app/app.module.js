angular.module("ConfiguratorApp", [ "ngMaterial", "Key" ])
	.config(function($mdThemingProvider) {
		$mdThemingProvider.theme('default')
			.primaryPalette('teal')
			.accentPalette('blue');
	})