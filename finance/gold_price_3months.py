import gold_price


if __name__ == "__main__":
    gold_td_data = gold_price.get_gold_data()
    last_3_months = gold_td_data.tail(100)
    print(last_3_months)
    gold_price.plot_gold_data(last_3_months)