<?php

function hf_advisories_installed_fields() {
    $t = get_t();
    return array(
        'hf_advisories_price' => array(
            'field_name' => 'hf_advisories_price',
            'label' => $t('Price of the product'),
            'type' => 'text'
        ),
        'hf_advisories_quantity' => array(
            'field_name' => 'hf_advisories_quantity',
            'label' => $t('Quantity of the product'),
            'type' => 'text'
        )
    );
}

function hf_advisories_installed_instances() {
    $t = get_t();
    return array(
        'hf_advisories_price' => array(
            'field_name' => 'hf_advisories_price',
            'type' => 'text',
            'label' => $t('Price of the product'),
            'widget' => array(
                'type' => 'text_textfield'
            ),
            'display' => array(
                'example_node_list' => array(
                    'label' => $t('Price of the product'),
                    'type' => 'text'
                )
            )
        ),
        'hf_advisories_quantity' => array(
            'field_name' => 'hf_advisories_quantity',
            'type' => 'text',
            'label' => $t('Quantity of the product'),
            'widget' => array(
                'type' => 'text_textfield'
            ),
            'display' => array(
                'example_node_list' => array(
                    'label' => $t('Quantity of the product'),
                    'type' => 'text'
                )
            )
        )
    );
}