angular.module("Layouts", [ "ngMaterial", "Key" ])
	.directive("fullLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/full.html",
			controller: function($scope) {
			}
		}
	})
	.directive("eightyLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/eightyLayout.html",
			controller: function($scope) {
			}
		}
	})
	.directive("sixtyLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/sixtyLayout.html",
			controller: function($scope) {
			}
		}
	})