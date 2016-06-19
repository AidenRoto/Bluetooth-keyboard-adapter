angular.module("Layouts", [ "ngMaterial", "Key" ])
	.directive("fullLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/full.html",
			controller: function($scope, keyboardDataService) {
				$scope.key_data = keyboardDataService.get_custom_settings();
				$scope.current_key = {};
				$scope.consumer_data = keyboardDataService.get_consumer_data();

				$scope.$on("selectEvnt", function(e, keyObj) {
					$scope.$broadcast("unselect");
					$scope.current_key = $scope.key_data[$scope.key_data.indexOf(keyObj)];
				})

				$scope.set_consumer_key = function(keyObj) {
					$scope.$broadcast("setConsumerKey", keyObj);
				}
			}
		}
	})
	.directive("mouseLayout", function() {
		return {
			restrict: "E",
			templateUrl: "app/component/layouts/mouse.html",
			controller: function($scope, keyboardDataService) {
				$scope.mouse_settings = keyboardDataService.get_mouse_settings();

				$scope.$on("selectEvnt", function(e, keyObj) {
					$scope.$broadcast("unselect");
				})

				$scope.add_one_pair = function() {
					$scope.mouse_settings.precisions.push({});
				}

				$scope.remove_pair = function(pair) {
					var idx = $scope.mouse_settings.precisions.indexOf(pair);
					$scope.mouse_settings.precisions.splice(idx, 1);
				}
			}
		}
	})