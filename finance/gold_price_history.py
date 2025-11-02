import gold_price


if __name__ == "__main__":
    gold_td_data = gold_price.get_gold_data()
    print(gold_td_data)
    gold_price.plot_gold_data(gold_td_data)