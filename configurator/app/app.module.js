angular.module("ConfiguratorApp", [ "ngMaterial", "Key", "Layouts" ])
	.config(function($mdThemingProvider) {
		$mdThemingProvider.theme('default')
			.primaryPalette('teal')
			.accentPalette('blue');
	})