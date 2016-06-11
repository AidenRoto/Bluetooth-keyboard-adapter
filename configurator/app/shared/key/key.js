angular.module("Key", [ "ngMaterial" ])
	.directive("key", function() {
		return {
			restrict: "E",
			scope: {
				keyObj: "="
			},
			templateUrl: "app/shared/key/key.html",
			controller: function($scope) {
				$scope.init_key = function() {
					$scope.selected = false;
				}

				$scope.click_key = function() {
					$scope.selected = !$scope.selected;
				}
			}
		}
	})