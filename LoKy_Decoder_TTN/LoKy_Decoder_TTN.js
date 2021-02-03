function LoKyDecode(bytes) {
    var data_types = {
        0  : {'size': 2, 'index': 'VccTIC (in V)', 'divisor': 1000	},        
        1  : {'size': 5, 'index': 'HCHC (in KWh)', 'divisor': 1000	},
        2  : {'size': 5, 'index': 'HCHP (in KWh)', 'divisor': 1000	},
        3  : {'size': 2, 'index': 'PTEC'		 , 'divisor': 1		},
        4  : {'size': 2, 'index': 'IINST  (in A)', 'divisor': 1		},
        5  : {'size': 3, 'index': 'PAPP  (in VA)', 'divisor': 1		},
        6  : {'size': 5, 'index': 'BASE (in KWh)', 'divisor': 1000	},
    };

	function arrayToDecimal(stream, divisor) {
	    var value = 0;
	    for (var i = 0; i < stream.length; i++) {
	        if (stream[i] > 0xFF)
	        	throw 'Byte value overflow!';
	        value = (value << 8) | stream[i];
	    }
	    value /= divisor;
	    return value;
	}

	var data = [];
	var i = 0;
		
		while (i < bytes.length) {
	    	var d_type = bytes[i++];
	    	if (typeof data_types[d_type] == 'undefined') {
	        throw 'Data type error!: ' + d_type;
	    	}

	    	var d_value = 0;
	    	var type = data_types[d_type];
	    	d_value = arrayToDecimal(bytes.slice(i, i + type.size), type.divisor);
	    	data.push({
	        			'type' : d_type,
	        			'index': type.index,
	        			'value': d_value,
	    			 });
	    	i += type.size;
		}

		return data;
}

// To use with TTN
function Decoder(bytes, fPort) {
    
    // flat output (like original decoder):
    var response = {};
    LoKyDecode(bytes, 0).forEach(function(field) {
    	response[field['index']] = field['value'];
    	});
    return response;
}