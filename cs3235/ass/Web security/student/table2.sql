USE cs3235;

CREATE TABLE `table2` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `voucher` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user` (`user`)
) ENGINE=MyISAM AUTO_INCREMENT=1247473648 DEFAULT CHARSET=utf8;

INSERT INTO table2(id, user, password, voucher) VALUES(1, 'you', '', '');
INSERT INTO table2(id, user, password, voucher) VALUES(!!VOUCHER_ID!!, 'vip', 'secretpassword', '!!FLAG_VALUE!!');

