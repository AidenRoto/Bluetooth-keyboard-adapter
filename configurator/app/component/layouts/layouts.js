angular.module("Layouts", [ "ngMaterial", "Key" ])
	.directive("fullLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/full.html",
			controller: function($scope, keyboardDataService) {
				$scope.key_data = keyboardDataService.get_custom_settings();

				$scope.$on("selectEvnt", function(e) {
					$scope.$broadcast("unselect");
				})
			}
		}
	})
	.directive("eightyLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/eightyLayout.html",
			controller: function($scope, keyboardDataService) {
			}
		}
	})
	.directive("sixtyLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/sixtyLayout.html",
			controller: function($scope, keyboardDataService) {
			}
		}
	})