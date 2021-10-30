# Performance Issue of `std::async` on Different Operating Systems

The following code comes from Daniel Hansons presentation at CppCon2019.

```cpp
void MCEuroOptPricer::computePriceAsync_() {
  EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_,
                           volatility_);
  generateSeeds_();

  std::vector<std::future<std::vector<double>>> futures;
  futures.reserve(numScenarios_);
  for (auto &seed : seeds_) {
    futures.push_back(std::async(epg, seed));
  }

  std::vector<double> discountedPayoffs;
  discountedPayoffs.reserve(numScenarios_);
  for (auto &future : futures) {
    double terminalPrice = future.get().back();
    double payoff = payoff_(terminalPrice);
    discountedPayoffs.push_back(discFactor_ * payoff);
  }

  double numScens = static_cast<double>(numScenarios_);
  price_ =
      quantity_ * (1.0 / numScens) *
      std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}
```

Up to now, only Microsoft's implementation uses thread pool (reuses the threads that has been created). 

This code runs poorly on Unix-like systems. Because pthread_create is an expensive operation and constantly creating new threads makes the function even slower than the non-paralleled version. 

Next Step: create a thread pool to accelerate Monte-Carlo simulation on Unix-like systems. 
