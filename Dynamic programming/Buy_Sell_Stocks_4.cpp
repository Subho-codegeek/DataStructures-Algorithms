class Solution
{
public:
    int solveUsingRec(vector<int> &prices, int i, int buy, int limit)
    {
        // bc
        if (i >= prices.size() || limit == 0)
        {
            return 0;
        }

        int profit = 0;
        // when buying is allowed
        if (buy)
        {
            int buyingProfit = -prices[i] + solveUsingRec(prices, i + 1, 0, limit); // 0 because it is bought
            int skipProfit = 0 + solveUsingRec(prices, i + 1, 1, limit);            // 1 becasue it is not bought
            profit = max(buyingProfit, skipProfit);
        }
        else
        {
            int sellingProfit = prices[i] + solveUsingRec(prices, i + 1, 1, limit - 1); // 1 because it is sold and buying is available
            int skipProfit = 0 + solveUsingRec(prices, i + 1, 0, limit);                // 0 becasue it is not sold and buying is not available
            profit = max(sellingProfit, skipProfit);
        }
        return profit;
    }

    int solveUsingMemo(vector<int> &prices, int i, int buy, vector<vector<vector<int>>> &dp, int limit)
    {
        // bc
        if (i >= prices.size() || limit == 0)
        {
            return 0;
        }

        if (dp[i][buy][limit] != -1)
        {
            return dp[i][buy][limit];
        }

        int profit = 0;
        // when buying is allowed
        if (buy)
        {
            int buyingProfit = -prices[i] + solveUsingMemo(prices, i + 1, 0, dp, limit); // 0 because it is bought
            int skipProfit = 0 + solveUsingMemo(prices, i + 1, 1, dp, limit);            // 1 becasue it is not bought
            profit = max(buyingProfit, skipProfit);
        }
        else
        {
            int sellingProfit = prices[i] + solveUsingMemo(prices, i + 1, 1, dp, limit - 1); // 1 because it is sold and buying is available
            int skipProfit = 0 + solveUsingMemo(prices, i + 1, 0, dp, limit);                // 0 becasue it is not sold and buying is not available
            profit = max(sellingProfit, skipProfit);
        }
        dp[i][buy][limit] = profit;
        return dp[i][buy][limit];
    }

    int solveUsingTabular(vector<int> &prices, vector<vector<vector<int>>> &dp, int k)
    {

        int n = prices.size() - 1;
        for (int i = n; i >= 0; i--)
        {
            for (int buy = 0; buy < 2; buy++)
            {
                for (int limit = 1; limit <= k; limit++)
                {
                    int profit = 0;
                    // when buying is allowed
                    if (buy)
                    {
                        int buyingProfit = -prices[i] + dp[i + 1][0][limit]; // 0 because it is bought
                        int skipProfit = 0 + dp[i + 1][1][limit];            // 1 becasue it is not bought
                        profit = max(buyingProfit, skipProfit);
                    }
                    else
                    {
                        int sellingProfit = prices[i] + dp[i + 1][1][limit - 1]; // 1 because it is sold and buying is available
                        int skipProfit = 0 + dp[i + 1][0][limit];                // 0 becasue it is not sold and buying is not available
                        profit = max(sellingProfit, skipProfit);
                    }
                    dp[i][buy][limit] = profit;
                }
            }
        }
        return dp[0][1][k];
    }

    int solveUsingSO(vector<int> &prices, vector<vector<vector<int>>> &dp, int k)
    {

        int n = prices.size() - 1;
        for (int i = n; i >= 0; i--)
        {
            for (int buy = 0; buy < 2; buy++)
            {
                for (int limit = 1; limit < k + 1; limit++)
                {
                    int profit = 0;
                    // when buying is allowed
                    if (buy)
                    {
                        int buyingProfit = -prices[i] + dp[1][0][limit]; // 0 because it is bought
                        int skipProfit = 0 + dp[1][1][limit];            // 1 becasue it is not bought
                        profit = max(buyingProfit, skipProfit);
                    }
                    else
                    {
                        int sellingProfit = prices[i] + dp[1][1][limit - 1]; // 1 because it is sold and buying is available
                        int skipProfit = 0 + dp[1][0][limit];                // 0 becasue it is not sold and buying is not available
                        profit = max(sellingProfit, skipProfit);
                    }
                    dp[0][buy][limit] = profit;
                }
            }
            dp[1] = dp[0];
        }
        return dp[0][1][k];
    }

    int maxProfit(int k, vector<int> &prices)
    {
        vector<vector<vector<int>>> dp(prices.size() + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
        // return solveUsingMemo(prices,0,1,dp,k);
        // return solveUsingTabular(prices,dp,k);
        return solveUsingSO(prices, dp, k);
    }
};